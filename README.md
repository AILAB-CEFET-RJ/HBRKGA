# HBRKGA
HBRKGA is a hyperparameter optimization method for Neural Networks based on BRKGA framework (http://mauricio.resende.info/src/brkgaAPI/).

## Requirements

Python 3.6
Tensorflow 1.13.1
Numpy 1.16.13
Pandas 0.24.2
SciKit Learn 0.21.1
Matplotlib 3.2.2
C++ STL

## Datasets

All datasets are publicly available at https://doi.org/10.5281/zenodo.4252922. Datasets must be placed in the [data](https://github.com/MLRG-CEFET-RJ/HBRKGA/tree/main/src/python/datasets) folder.

## Usage

Install/load the requirements packages.

To setup the dataset, go to the C++ to python bridge in evaluate function at [data](https://github.com/MLRG-CEFET-RJ/HBRKGA/blob/main/src/random_walk.cpp) and specifies one dataset:
```
python ./src/python/neural_network.py fashion (Fashion MNIST)
python ./src/python/neural_network.py mnist (MNIST)
python ./src/python/neural_network.py rectangles (Rectangles)
python ./src/python/neural_network.py cosmos (COSMOS)
```
This process can be also add to python [data](https://github.com/MLRG-CEFET-RJ/HBRKGA/blob/main/src/python/neural_network.py) file with another trainning/validation set.

To setup the hyperparameters go to [data](https://github.com/MLRG-CEFET-RJ/HBRKGA/blob/main/src/BRKGA/SampleDecoder.cpp) and edit/add the Sample Decoder par_dom.
Each par_dom represents a hyperparameter with min/max value to optimize.
```
	par_dom.push_back(make_pair(1000,2000));
	par_dom.push_back(make_pair(2000,4000));
	par_dom.push_back(make_pair(2000,6000));
	par_dom.push_back(make_pair(0.000001,0.1));
	par_dom.push_back(make_pair(0,0.001));
```

To compile the C++ project:
```
make clean
make
```

To execute the HBRKGA optimization process:
```
nohup ./bin/hypAG > hbrkga.log &
```


## Contact
To give your opinion about this work, send an email to `marcello.serqueira@eic.cefet-rj.br`.
