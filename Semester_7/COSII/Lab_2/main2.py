from PIL import Image, ImageEnhance
import numpy as np
import matplotlib.pyplot as plt
from skimage import filters, measure, color, morphology, feature
from sklearn.cluster import KMeans
import pandas as pd
from sklearn.preprocessing import StandardScaler

# Load the image
image_path = 'P0001470.jpg'
original_image = Image.open(image_path)

# Convert image to RGB and grayscale
rgb_image = original_image.convert('RGB')
gray_image = original_image.convert('L')

# Enhance Contrast
enhanced_image = ImageEnhance.Contrast(gray_image).enhance(2.0)

# Convert grayscale image to binary using a threshold
threshold = filters.threshold_otsu(np.array(enhanced_image))
binary_image = np.array(enhanced_image) > threshold

# Morphological operations
cleaned_binary_image = morphology.remove_small_objects(binary_image, min_size=50)
cleaned_binary_image = morphology.remove_small_holes(cleaned_binary_image, area_threshold=50)

# Label connected regions
label_image = measure.label(cleaned_binary_image, connectivity=2)

# Calculate properties of labeled image regions
properties = measure.regionprops_table(label_image, properties=('area', 'perimeter', 'eccentricity', 'solidity', 'moments_central'))

# Adding texture features
lbp = feature.local_binary_pattern(np.array(gray_image), P=8, R=1, method='uniform')
for region in measure.regionprops(label_image):
    minr, minc, maxr, maxc = region.bbox
    region_lbp = lbp[minr:maxr, minc:maxc]
    properties[f'lbp_{region.label}'] = region_lbp.mean()

# Convert properties to DataFrame
properties_df = pd.DataFrame(properties)

# Normalize the features
scaler = StandardScaler()
features = scaler.fit_transform(properties_df)

# Apply k-means clustering
k = 2
kmeans = KMeans(n_clusters=k)
clusters = kmeans.fit_predict(features)

# Add cluster information to the dataframe
properties_df['cluster'] = clusters

# Display the labeled image with cluster labels
fig, ax = plt.subplots(figsize=(6, 6))
ax.imshow(label_image, cmap='nipy_spectral')

# Annotate each region with cluster label
for region in measure.regionprops(label_image):
    if region.area >= 50:
        minr, minc, maxr, maxc = region.bbox
        cluster_label = clusters[region.label - 1]
        ax.text(minc, minr, f'Cluster {cluster_label}', fontsize=12, color='red')

plt.show()

# Save the modified image
output_image_path = 'labeled_clusters.png'
fig.savefig(output_image_path)

output_image_path, properties_df.head()
