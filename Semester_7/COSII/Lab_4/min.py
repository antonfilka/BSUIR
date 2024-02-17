import numpy as np
from sklearn.neural_network import MLPClassifier


def convert_to_array(matrix):
    return np.array(matrix).flatten().astype(int)


def convert_pattern(pattern):
    conversion = {'-': 0, '+': 1}
    return np.array([[conversion[char] for char in row] for row in pattern]).flatten()


def add_noise(pattern, noise_level=0.1):
    noisy_pattern = pattern.copy()
    for i in range(len(noisy_pattern)):
        if np.random.rand() < noise_level:
            noisy_pattern[i] = 1 - noisy_pattern[i]
    return noisy_pattern


ideal_patterns = [
    [
        ['+', '+', '+', '+', '+', '+'],
        ['-', '-', '+', '+', '-', '-'],
        ['-', '-', '+', '+', '-', '-'],
        ['-', '-', '+', '+', '-', '-'],
        ['-', '-', '+', '+', '-', '-'],
        ['-', '-', '+', '+', '-', '-']
    ],
    [
        ['+', '-', '-', '-', '-', '+'],
        ['-', '+', '-', '-', '+', '-'],
        ['-', '-', '+', '+', '-', '-'],
        ['-', '-', '+', '+', '-', '-'],
        ['-', '+', '-', '-', '+', '-'],
        ['+', '-', '-', '-', '-', '+']
    ],
    [
        ['-', '-', '+', '+', '-', '-'],
        ['-', '+', '-', '-', '+', '-'],
        ['+', '-', '-', '-', '-', '+'],
        ['+', '-', '-', '-', '-', '+'],
        ['-', '+', '-', '-', '+', '-'],
        ['-', '-', '+', '+', '-', '-']
    ],
    [
        ['+', '+', '+', '+', '+', '+'],
        ['+', '-', '-', '-', '-', '+'],
        ['+', '-', '-', '-', '-', '+'],
        ['+', '-', '-', '-', '-', '+'],
        ['+', '-', '-', '-', '-', '+'],
        ['+', '+', '+', '+', '+', '+']
    ],
    [
        ['-', '-', '+', '+', '-', '-'],
        ['-', '-', '+', '+', '-', '-'],
        ['+', '+', '-', '-', '+', '+'],
        ['+', '+', '-', '-', '+', '+'],
        ['-', '-', '+', '+', '-', '-'],
        ['-', '-', '+', '+', '-', '-']
    ],
]
numerical_patterns = [convert_pattern(pattern) for pattern in ideal_patterns]
labels = np.arange(len(ideal_patterns))
noisy_patterns = []

for pattern in numerical_patterns:
    for _ in range(3):
        noisy_patterns.append(add_noise(pattern))
mlp = MLPClassifier(hidden_layer_sizes=(50,), max_iter=1000, random_state=1)
mlp.fit(numerical_patterns, labels)
predictions = mlp.predict(noisy_patterns)
first_noisy_pattern = noisy_patterns[0].reshape(6, 6)

print("Recognized Noisy Pattern:")
print(first_noisy_pattern)

probabilities = mlp.predict_proba([noisy_patterns[0]])[0] * 100

print("Probability Match with Each Class:")
print(probabilities)
print("Number of Steps for Training:", mlp.n_iter_)
