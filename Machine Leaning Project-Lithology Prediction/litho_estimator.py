# import
import pandas as pd
import numpy as np

# for preprocessing
from sklearn.model_selection import train_test_split
from sklearn.compose import ColumnTransformer
from sklearn.pipeline import Pipeline
from sklearn.preprocessing import StandardScaler, OneHotEncoder, LabelEncoder
from sklearn.impute import SimpleImputer

# for model
from sklearn.linear_model import LogisticRegression

# for metrics
from sklearn.metrics import f1_score

# for PCA
from sklearn.decomposition import PCA

# Add any other imports that you need here

# If you created custom transformers or helper functions, you can also add them to this file.


class LithoEstimator:
    """Used to predict lithology in IODP wells. The signature (method name, argument and return types) for the strict minimum number of methods needed are already written for you below.
    Simply complete the methods following your own notebook results. You can also add more methods than provided below in order to keep your code clean."""

    def __init__(self, path: str = "data/log_data.csv") -> None:
        """The path is a path to the training file. The default is the file I gave you.
        You want to create an X_train, X_test, y_train and y_test following the same principle as in your
        notebook. You also want to define and train your estimator as soon as you create it.

        I recommend creatubg the following instance variables in your __init__ method:
        self.X_train, self.X_test, self.y_train, self.y_test
        self.encoder - the label encoder for your categories
        self.model - the entire trained model pipeline

        Note that this class should not handle hyperparameter searching or feature selection - if you did those in your Part B
        simply use your best estimators.

        """
        self.X_train, self.X_test, self.y_train, self.y_test = self.load_and_split(path)
        self.get_model()

    def load_and_split(self, path):
        """Loads the data and splits it into X_train, X_test, y_train and y_test.
        Returns the X_train, X_test, y_train and y_test."""
        df = pd.read_csv(path)
        df.drop_duplicates(inplace=True)

        X = df.drop(columns="lithology")
        y = df["lithology"]

        return train_test_split(X, y, test_size=0.3, random_state=42)

    def x_test_score(self) -> np.float:
        """Returns the F1 macro score of the X_test. This should be of type float."""

        return f1_score(
            self.y_test_cat, self.model.predict(self.X_test), average="macro"
        )

    def get_Xs(self) -> (pd.DataFrame, pd.DataFrame):
        """Returns the X_train and X_test. This method is already written for you."""

        return self.X_train, self.X_test

    def get_ys(self) -> (pd.DataFrame, pd.DataFrame):
        """Returns the y_train and y_test. This method is already written for you."""

        return self.y_train, self.y_test

    def predict(
        self, path_to_new_file: str = "data/new_data.csv", store_result=False
    ) -> np.array:
        """Uses the trained algorithm to predict and return the predicted labels on an unseen file.
        The default file is the unknown_data.csv file in your data folder.

        Return a numpy array (the default for the "predict()" function of sklearn estimator)"""
        X = pd.read_csv(path_to_new_file)
        y_pred_encoded = self.model.predict(X)
        y_pred = self.l_encoder.inverse_transform(y_pred_encoded)
        if store_result:
            pd.Series(y_pred, name="y_pred").to_csv("y_pred_notebook.csv", index=False)
        return y_pred

    def get_model(self) -> Pipeline:
        """returns the entire trained pipeline, i.e. your model.
        This will include the data preprocessor and the final estimator."""
        num_data = self.X_train.select_dtypes(exclude=["object"]).columns.tolist()
        cat_data = self.X_train.select_dtypes(include="object").columns.tolist()

        num_data.remove("HFK")
        num_data.remove("HTHO")
        num_data.remove("IMPH")

        self.l_encoder = LabelEncoder().fit(self.y_train)
        self.y_train_encoded = self.l_encoder.transform(self.y_train)
        self.y_test_cat = self.l_encoder.transform(self.y_test)

        num_transformer = Pipeline(
            [("num_imputer", SimpleImputer()), ("num_scaler", StandardScaler())]
        )

        # Encode categorical variables
        cat_transformer = Pipeline(
            [
                ("cat_imputer", SimpleImputer(strategy="most_frequent")),
                (
                    "cat_encoder",
                    OneHotEncoder(handle_unknown="ignore", sparse_output=False),
                ),
            ]
        )

        preprocessor = ColumnTransformer(
            [
                ("num_transformer", num_transformer, num_data),
                ("cat_transformer", cat_transformer, cat_data),
            ]
        )

        pca_compressed = PCA(n_components=8, random_state=42)

        self.model = Pipeline(
            [
                ("preprocessor", preprocessor),
                ("pca", pca_compressed),
                (
                    "classifier",
                    LogisticRegression(
                        C=1,
                        class_weight="balanced",
                        l1_ratio=0.5,
                        max_iter=3000,
                        multi_class="ovr",
                        penalty="elasticnet",
                        random_state=42,
                        solver="saga",
                    ),
                ),
            ]
        )

        self.model.fit(self.X_train, self.y_train_encoded)

        return self.model