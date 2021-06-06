import datetime
from bayes_opt import BayesianOptimization
opening = datetime.datetime.now() #execution time start
import os, logging
import tensorflow as tf
import numpy as np
import data_utils as du
import sys
import warnings
import matplotlib.pyplot as plt
from sklearn.metrics import precision_score, f1_score, recall_score, accuracy_score
warnings.filterwarnings("ignore")
logging.disable(logging.WARNING)
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'
from sklearn.metrics import f1_score
import pathlib

'''
System args: LAYER1, LAYER2, LAYER3, LR, BETA
LAYER1 = Neurons number in the first hidden layer
LAYER2 = Neurons number in the second hidden layer
LAYER3 = Neurons number in the third hidden layer
LR = learning rate
BETA = beta parameter to regularization. 0 to ignore
'''

#Train/dev/test path whitespace separated file without header. Target in the last column (data_utils)
current_script_path = str(pathlib.Path(__file__).parent.absolute())
if str(sys.argv[1]) == 'cosmos':
  train_path =  current_script_path + "/dataset/cosmos_train_SMOTE.csv" #COSMOS
  test_path = current_script_path + "/dataset/cosmos_val.csv"
  hyper_args = du.hyper_space('cosmos')

if str(sys.argv[1]) == 'rectangles':
  train_path =  current_script_path + "/datasets/rectangles_train.csv" #RECTANGLES
  test_path = current_script_path + "/datasets/rectangles_val.csv"
  hyper_args = du.hyper_space('others')

if str(sys.argv[1]) == 'mnist':
  train_path =  "/mnt/sdb/home2/mserqueira/COSMOS/dataset/mnist_train.csv" #RECTANGLES
  test_path = "/mnt/sdb/home2/mserqueira/COSMOS/dataset/mnist_val.csv"
  hyper_args = du.hyper_space('others')

if str(sys.argv[1]) == 'mnist_back_rot':
  train_path =  "/mnt/sdb/home2/mserqueira/BRKGA/src/python/datasets/mnist_all_background_images_rotation_normalized_train.csv" #RECTANGLES
  test_path = "/mnt/sdb/home2/mserqueira/BRKGA/src/python/datasets/mnist_all_background_images_rotation_normalized_val.csv"
  hyper_args = du.hyper_space('others')

if str(sys.argv[1]) == 'fashion':
  train_path =  "/home/mserqueira/COSMOS/dataset/fashion_mnist_train.csv" #RECTANGLES
  test_path = "/home/mserqueira/COSMOS/dataset/fashion_mnist_val.csv"
  hyper_args = du.hyper_space('others')

epochs_no = 300 #Number of epochs
batch_size = 50000#1024
patience = 10#13 #Number of trials to reduce epoch loss based on the min_delta
min_delta = 0.3 #0.1 #min MSE reduction in each epoch
patience_cnt = 0
prior = float("inf")

trainX, trainY, predX, predY, n_classes = du.csv_to_numpy_array(train_path, test_path)
num_x = trainX.shape[1]
num_y = trainY.shape[1]

def neural_network(LAYER1, LAYER2, LAYER3, x, y):
  #  with tf.device('/device:GPU:0'):
  W1 = tf.Variable(tf.random_normal([num_x, LAYER1]))
  b1 = tf.Variable(tf.random_normal([LAYER1]))
  
  W2 = tf.Variable(tf.random_normal([LAYER1, LAYER2]))
  b2 = tf.Variable(tf.random_normal([LAYER2]))
  
  W3 = tf.Variable(tf.random_normal([LAYER2, LAYER3]))
  b3 = tf.Variable(tf.random_normal([LAYER3]))
  
  W_out = tf.Variable(tf.random_normal([LAYER3, n_classes]))
  b_out = tf.Variable(tf.random_normal([n_classes]))
  
  Z1 = tf.add(tf.matmul(x, W1), b1)
  A1 = tf.nn.relu(Z1)
  
  Z2 = tf.add(tf.matmul(A1, W2), b2)
  A2 = tf.nn.relu(Z2)
  
  Z3 = tf.add(tf.matmul(A2, W3), b3)
  A3 = tf.nn.relu(Z3)
  
  Z_out = tf.matmul(A3, W_out) + b_out

  return Z_out, W_out

def models_predictions(prediction, sess, x, y):
  pred_model =  tf.argmax(prediction, 1)
  pred_model = sess.run(pred_model, feed_dict={x:predX, y:predY})
  pred_true =  tf.argmax(y, 1)
  pred_true = sess.run(pred_true, feed_dict={x:predX, y:predY})

  train_model = tf.argmax(prediction, 1)
  train_model = sess.run(train_model, feed_dict={x:trainX, y:trainY})
  train_true =  tf.argmax(y, 1)
  train_true = sess.run(train_true, feed_dict={x:trainX, y:trainY})

  return pred_model, pred_true, train_model, train_true

def early_stop(epoch, epoch_loss):
  global patience_cnt
  global prior
  if epoch == 0:
    patience_cnt = 0
    prior = float("inf")
  if epoch > 0 and prior - epoch_loss > min_delta:
    patience_cnt = 0
    flag = False
  else:
    patience_cnt += 1
    flag = False
  if patience_cnt > patience:
    flag = True
    patience_cnt = 0
    prior = float("inf")
  prior = epoch_loss
  return flag

def learning_plot(loss_train, loss_test):
  epoch_plot = range(0,len(loss_train))
  epoch_plot
  loss_test
  loss_train
  plt.plot(epoch_plot, loss_train, label="Train error")
  plt.plot(epoch_plot, loss_test, label="Test error")
  plt.legend(loc='lower left', bbox_to_anchor= (0.0, 1.01), ncol=2, 
    borderaxespad=0, frameon=False)
  #plt.legend(loc='upper right')
  plt.ylabel('Error')
  plt.xlabel('Epoch')
  plt.savefig('learning_plot.pdf')
  pass

def get_error(prediction, y, sess, labelX, labelY, x):
  correct_pred = tf.equal(tf.argmax(prediction, 1), tf.argmax(y, 1))
  accuracy = tf.reduce_mean(tf.cast(correct_pred, tf.float32))
  error = 1-sess.run(accuracy, feed_dict={x: labelX, y: labelY})

  return error

def build_graph(layer1, layer2, layer3, learning_rate, beta):
    # with tf.device('/device:GPU:1'):
    x = tf.placeholder(tf.float32, [None, num_x])
    y = tf.placeholder(tf.float32, [None, num_y])
    lr = tf.placeholder(tf.float32)
    prediction, weights = neural_network(int(layer1), int(layer2), int(layer3), x, y)
    
    loss = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(logits=prediction, labels=y)) #Ou reduce_sum
    regularizer = tf.nn.l2_loss(weights) #L2
    loss = tf.reduce_mean(loss + round(beta, 6) * regularizer)
    
    optimizer = tf.train.AdamOptimizer(lr).minimize(loss)
    loss_train = []
    loss_test = []
    f1_best = 0

    with tf.Session() as sess:
      sess.run(tf.global_variables_initializer())
      for epoch in range(epochs_no):
        epoch_loss = 0
        i=0
        while i < len(trainX):
          start = i
          end = i+batch_size
          batch_x = np.array(trainX[start:end])
          batch_y = np.array(trainY[start:end])
          _, c = sess.run([optimizer, loss], feed_dict={x: batch_x, y: batch_y, lr: round(learning_rate, 6)})
          epoch_loss += c
          i+=batch_size
        early_flag = early_stop(epoch, epoch_loss)
        f1_epoch = get_f1(prediction, y, sess, predX, predY, x)
        if f1_epoch > f1_best:
          f1_best = f1_epoch
        #if early_flag == False:
          #print('Epoch ', epoch+1, 'of ', epochs_no, '| loss: ', epoch_loss)
        if early_flag == True:
          #print("Early stopping... ", 'Epoch', epoch+1, 'of', epochs_no, '| loss:', epoch_loss)
          break
      
      loss_train.append(get_error(prediction, y, sess, trainX, trainY, x))
      loss_test.append(get_error(prediction, y, sess, predX, predY, x))
      #if f1 > best_model: #To save the best model
        #saver = tf.train.Saver()
        #saver.save(sess, 'TF_model/sess/AutoML_model.ckpt')
        #np.savetxt("TF_model/test_classification.csv", pred_model.astype(int), delimiter=",")
        #print("\nBest model saved in TF_model folder")

      sess.close()

    learning_plot(loss_train, loss_test)
    print(round(f1_best, 3))
    return f1_best

def get_f1(prediction, y, sess, predX, predY, x):
  pred_model =  tf.argmax(prediction, 1)
  pred_model = sess.run(pred_model, feed_dict={x:predX, y:predY})
  pred_true =  tf.argmax(y, 1)
  pred_true = sess.run(pred_true, feed_dict={x:predX, y:predY})
  f1 = f1_score(pred_true, pred_model, average='macro')

  return f1

def main():
  layer1 = int(sys.argv[2])
  layer2 = int(sys.argv[3])
  layer3 = int(sys.argv[4])
  lr = float(sys.argv[5])
  rr = float(sys.argv[6])
  build_graph(layer1, layer2, layer3, lr, rr)
  return 0

if __name__ == "__main__":
  main()