# HBRKGA
HBRKGA is a hyperparameter optimization method for Neural Networks based on BRKGA framework (http://mauricio.resende.info/src/brkgaAPI/). We have done experiments comparing HBRKGA with some hyperparameter optimization methods. The results and description of our proposal can be found at https://arxiv.org/abs/2011.11062.

![hbrkga_flux](https://github.com/MLRG-CEFET-RJ/HBRKGA/blob/main/hbrkga.png)

## Setup

The setup can be divided in three major steps:

1. Installing necessary software
2. Configuring Conda environment
3. Configuring Makefile and building the project

### Installing necessary software

[Anaconda](https://www.anaconda.com) is recommended to create a python virtual environment. Additionally, it is recommended to install TensorFlow with GPU support, if available.

[This page](https://www.tensorflow.org/install/gpu) presents the steps needed to install Tensorflow with GPU support. If you are using WSL and have a graphics card available follow [this tutorial to install Tensorflow with DirectML](https://docs.microsoft.com/en-us/windows/win32/direct3d12/gpu-tensorflow-wsl) instead.

### Configuring Conda environment

The following requirements are needed to install in your conda environment.

* Python 3.6
* Tensorflow 1.15
* Bayesian Optimization
* Pandas
* Matplotlib
* Pybind11
* Scikit Learn

You can install the packages above in a conda environment by running the commands below.
```
conda create -n hbrkga python=3.6 tensorflow-gpu matplotlib scikit-learn pandas -y
conda activate hbrkga
conda install -c conda-forge bayesian-optimization -y
```

If you are on WSL and would like to enable GPU support, you may use the `env-wsl.yml` in this repository to create the conda environment with the command below.

```
conda env create -f env-wsl.yml
```

If you would like to create the environment from scratch, just replace `tensorflow-gpu` with `tensorflow-directml`.

```
conda create -n hbrkga python=3.6 tensorflow-directml matplotlib scikit-learn pandas -y
conda activate hbrkga
conda install -c conda-forge bayesian-optimization -y
```

### Configuring Makefile and building the project

With the conda environment activated, run the two steps below to configure

1. Run `python3 -m pybind11 --includes` and add the output of the command to the `PYTHON_INCLUDES` variable in the Makefile at the root of the project.

2. Run `python3-config --extension-suffix` and paste the output of it to the variable `EXTENSION` to the Makefile in the root of the project.

3. Once the variables were set up correctly, the project can be compiled by running.

```
make clean
make
```

## Additional Steps

1. Install gdb, if you need debugging. On Ubuntu, you can do so by running `sudo apt install gdb`.

## Usage

HBRKGA can be used as a function of the module `hbrkga`. test.py illustrates the usage of it. Note that the python script must be in the same directory as the library built, or the path containing the library must be added to the `PYTHONPATH` environment variable.

## Current Limitations

At this point, the only model available to optimize is a three-layer fully connected neural network, with the following parameters:

* The number of neurons for the first, second and third layers
* The learning rate
* The regularization parameter (beta)

## Future Work

The following steps could be implemented to evolve the code in this repository:

* Enable different models to be optimized, other than a three-layer fully connected neural network
* Allow users to use different datasets (sent as parameters)
* Facilicate the setup process (find a way to activate the conda environment during the Makefile execution to avoid having to set up variables manually)
* Publish the project as a Python package

## Citation
```
@article{serqueira2020population,
  title={A Population-based Hybrid Approach to Hyperparameter Optimization for Neural Networks},
  author={Serqueira, Marcello and Gonz{\'a}lez, Pedro and Bezerra, Eduardo},
  journal={arXiv preprint arXiv:2011.11062},
  year={2020}
}
```

## Contact
To give your opinion about this work, send an email to `marcello.serqueira@eic.cefet-rj.br`.
