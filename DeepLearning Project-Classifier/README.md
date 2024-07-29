## DL module coursework 2

<img src="https://drive.google.com/uc?id=1DG7dis2Daa9MObZP7pK5HBMBQiHMED-D" width="700"/>


<br>

## **Tasks**

### Task 1
Classify the hand images in the `test_hands` folder using any method you have learned during the module. The classifier should classify test hands using the following labels:

- `0`: real hand
- `1`: VAE hand
- `2`: GAN hand

<br>

### Task2
Answer the two questions at the end of this README file. Answer them in the README itself and commit and push your modified README file to your repository.

<br>



## Deliverables

Your final repository should contain the following:

1. `acse-xz4019_classified_hands.csv`: a comma-separated value file with the name of the hand in the test set, then a comma, and then the prediction for this hand image. It should look like:

	```
	test_hand_0001.jpeg, 2
	test_hand_0002.jpeg, 0
	...
	```
with the appropriate lable values that your classifier generates. Add this new file to the repo and do not put it inside any subfolder please.

2. `acse-xz4019_DLcw2_clean.ipynb`: a clean notebook with the classifier workflow, includes data preparation, network implementation, final training, final evaluation of the test set, writing of the csv file. 

3. `acse-xz4019_DLcw2_hypertune.ipynb`: a notebook where explore the best hyperparameter values for the final network design.


4. `README.md` — Modified version of this README file that includes the answers to the questionsbelow.

5. `references.md` — List of the references that have used.

<br>

## **Task 1 - Classifier**

### Datasets
You will find the following folders in this repository:
- `real_hands`: contains real hands.
- `VAE_hands`: contains hands generated using VAEs.
- `GAN_hands`: contains hands generared using GANs.
- `test_hands`: contains a mix of real hands, VAE-generated hands, and GAN-generated hands.

Use the labels for predictions:

- real hands (label: `0`)
- VAE-generated hands (label: `1`)
- GAN-generated hands (label: `2`)

<br>

## **Task 2 - Questions**
Answer the questions below.

### Question 1 [150 words maximum]
If I asked you to do the first coursework again, but now I gave you 5 days and 500 compute units (instead of 100 compute units), what would you do differently to improve your results. In this case, you would be able to use any architecture we have seen in class. Justify your answers well, and do not go over the word limit. You can use bullet points and a maximum of one diagram/figure/table to support your answer.

### ANSWER to question 1:

My enhanced strategy includes:
- **Diverse Data Sourcing from Kaggle**: I'll acquire a broad range of high-quality datasets from real hands to maximise model generalisation.
- **Advanced Transfer Learning**: Initially training on a comprehensive open-source dataset, followed by fine-tuning with x-ray hand data, to address limited domain data effectively.
- **Sub-Labelling for Precision**: Implementing sub-labelling, such as distinguishing between left and right-hand images, to refine training accuracy and overcome previous model limitations of blended left and right-hand features due to broad training
Focused Image Generation with CGANs: Using Conditional Generative Adversarial Networks to generate images with specific attributes, enhancing control over outputs.
- **Intensive Hyperparameter Optimisation**: Employing a much more massive grid search for thorough hyperparameter tuning, vital for model enhancement.
- **Parallel Processing Utilizing Increased Compute Capacity**: Strategically deploying additional compute units for parallel processing, enabling the training of larger models and multiple concurrent experiments.

<br>

### Question 2 [100 words maximum]
Additionally to the newly defined hypotethical assessment in **Question 1**, if i told you that now the images were 512x512 pixels instead of 32x32, and I gave you a choice between these two extra resources:

**a.** as much compute power as you want, but only have the 10000 images provided. <br>
**b.** as many more images in your dataset as you want, but only have the 500 compute units availabe.

Which one would you choose and why? Again justify your answers and use bullet points or tables as you see fit.

### ANSWER to question 2:

I will choose b. Although the image increased in size, and the training model will become more computationally expensive, 500 compute units can let me use V100 for four days without rest. It is far more than enough. With an abundant dataset, I could train a deep model without worrying it doesn't converge due to overfitting, and it can capture more features, making the model more robust.
On the other hand, the performance would be reasonable if I had enough data, even training a simpler network. A model with fewer parameters can also prevent overfitting and be easily trained.
| Hardware | Consumption (in units) |
|----------|------------------------|
| CPU      | 0.08                   |
| T4       | 1.96                   |
| V100     | 5.36                   |
| TPU      | 1.96                   |






