from PIL import Image
import numpy as np
import matplotlib.pyplot as plt
from skimage import filters, measure, morphology
from sklearn.cluster import KMeans
import pandas as pd
from sklearn.preprocessing import StandardScaler
import matplotlib.patches as patches

# Load the image
image_path = 'P0001470.jpg'
original_image = Image.open(image_path)

# Convert image to grayscale
gray_image = original_image.convert('L')

# Apply a global threshold to binarize the image
threshold = filters.threshold_otsu(np.array(gray_image))
binary_image = np.array(gray_image) > threshold

# Morphological cleaning
cleaned_binary_image = morphology.binary_opening(binary_image, morphology.disk(3))  # Use a disk of size 3
cleaned_binary_image = morphology.remove_small_objects(cleaned_binary_image, min_size=200)  # Remove objects smaller than 200 pixels

# Label connected regions
label_image = measure.label(cleaned_binary_image)

# Extract features that may be relevant for differentiating spoons and sugar cubes
properties = ['area', 'eccentricity', 'solidity', 'extent', 'major_axis_length', 'minor_axis_length']
props = measure.regionprops_table(label_image, properties=properties)
properties_df = pd.DataFrame(props)

# Calculate additional features like aspect ratio
properties_df['aspect_ratio'] = properties_df['major_axis_length'] / properties_df['minor_axis_length']

# Standardize the features
scaler = StandardScaler()
features = scaler.fit_transform(properties_df)

# K-means clustering
kmeans = KMeans(n_clusters=4)
clusters = kmeans.fit_predict(features)

# Add cluster information to the properties dataframe
properties_df['cluster'] = clusters


# Plot the original image and label the objects based on the cluster
fig, ax = plt.subplots(figsize=(8, 6))
ax.imshow(original_image)

# To store the positions for labeling the clusters
positions = []

for index, region in enumerate(measure.regionprops(label_image)):
    # take regions with large enough areas
    if region.area >= 200:
        # Draw the bounding box
        minr, minc, maxr, maxc = region.bbox
        cluster_label = clusters[index]
        rect = patches.Rectangle((minc, minr), maxc - minc, maxr - minr, 
                                 edgecolor='red' if cluster_label else 'blue', 
                                 facecolor='none')
        ax.add_patch(rect)
        # Save the position for the cluster label
        positions.append((minc, minr, cluster_label))

# Label the clusters
for pos in positions:
    ax.text(pos[0], pos[1], f'Cluster {pos[2]}', 
            bbox=dict(facecolor='white', alpha=0.5), fontsize=8)

plt.title('Clustered Objects')
plt.show()

# Save the clustered image
output_image_path = 'clustered_objects.png'
fig.savefig(output_image_path)

# Return the path to the modified image and the properties with cluster labels
(output_image_path, properties_df.head())
