## Deep Learning project 1



# Build a generative model that creates X-ray images of hands

<img src="https://drive.google.com/uc?id=1LubLuuyiJwyDNRd2Wj0vaA0Ek2AtAFxH" width="500"/>


<br>

## **Task**:
Create a generative model, either a VAE or a GANs, train it, and use it to generate 300 new samples (new images) of X-ray images of hands. <br>

Justify your choice (there is a dedicated text cell in the 'clean' notebook. There is no right or wrong here, but the quality of the justification will be assessed.


## **Dataset**:
You have 8000 samples available in the repository under the folder `real_hands` that you can use to train your VAE or your GAN.

## **Deliverables**:
1. `GAN_hands` — folder containting the 300 samples generated from model. The format is `jpeg`. The sizes of the generated images is the same as the ones in the training set. <br>


2. `acse-xz4019_DLcw1_clean.ipynb` — 'clean' notebook containing the code and supporting explanatory text for:
	- Data preparation
	- Design and implementation of your network of choice (VAE or GAN)
	- Implementation of training loops and any other utility functions you see fit
	- Executed cells for network training with accompanying loss evolution plots.
	- Generation of 300 samples by using the trained model.


3. `acse-xz4019_DLcw1_hypertune.ipynb` — An 'auxiliary' notebook containting hyperparameter explorations have done to decide what are the best hyperparameters to use for your final training.

4. `references.md` — List of your references used in the template references.md.

