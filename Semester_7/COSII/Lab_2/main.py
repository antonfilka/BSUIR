from PIL import Image
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from skimage import filters, measure, color, morphology

# Load image
image_path = 'P0001470.jpg'
image = Image.open(image_path)

# Convert image to grayscale
image_gray = image.convert('L')

# 1. Correct brightness of the image if necessary
# We will perform histogram equalization to improve the brightness/contrast
image_eq = Image.fromarray(np.uint8(plt.hist(image_gray.getdata(), bins=256, cumulative=True)[0]))

# 2. Convert color image to binary image.
# We will use Otsu's method to find the threshold for binarization
threshold_value = filters.threshold_otsu(np.array(image_gray))
image_binary = (np.array(image_gray) > threshold_value).astype(np.uint8)

# 3. Implement threshold binarization of the image
# Otsu's method already provides threshold binarization, which we have done above

# 4. Extract four-connected areas in the image.
# We will use skimage's label function with connectivity set to 1 (for four-connectivity)
connected_components = measure.label(image_binary, connectivity=1)

# We will add numbered labels to each object on the labeled image
labeled_image = color.label2rgb(connected_components, bg_label=0)

# 5. Determine the properties of objects, calculate a feature system for objects
# represented on the image (area, perimeter, compactness, elongation, statistical moments).
properties = measure.regionprops_table(connected_components, properties=('area', 'perimeter', 'solidity', 'eccentricity', 'moments_central'))


properties_df = measure.regionprops_table(connected_components, properties=('label', 'area', 'perimeter', 'solidity', 'eccentricity'))
properties_df = pd.DataFrame(properties_df)
# 6. Using the k-means algorithm and a measure of similarity, determine the
# object's membership in one of the clusters (classes).
# Before we can apply k-means, we need to decide on the number of clusters, k.
# Here, we will choose k arbitrarily as 3 for demonstration purposes.

# We will perform k-means clustering on the features we have just computed.
# For simplicity, let's use only area and perimeter for k-means clustering.
from sklearn.cluster import KMeans

# Prepare the features for k-means clustering
features = np.column_stack((properties['area'], properties['perimeter']))

# Perform k-means clustering
kmeans = KMeans(n_clusters=3, random_state=0).fit(features)

# Assign labels to the original components
for region, cluster_label in zip(measure.regionprops(connected_components), kmeans.labels_):
    coords = region.coords
    for coord in coords:
        connected_components[coord[0], coord[1]] = cluster_label

# Create a new figure with subplots for each property
fig, axes = plt.subplots(2, 2, figsize=(14, 10))

# Plot each property in a separate subplot
axes[0, 0].bar(properties_df['label'], properties_df['area'], color='blue')
axes[0, 0].set_title('Area')
axes[0, 0].set_xlabel('Label')
axes[0, 0].set_ylabel('Pixels')

axes[0, 1].bar(properties_df['label'], properties_df['perimeter'], color='green')
axes[0, 1].set_title('Perimeter')
axes[0, 1].set_xlabel('Label')
axes[0, 1].set_ylabel('Pixels')

axes[1, 0].bar(properties_df['label'], properties_df['solidity'], color='red')
axes[1, 0].set_title('Solidity')
axes[1, 0].set_xlabel('Label')
axes[1, 0].set_ylabel('Ratio')

axes[1, 1].bar(properties_df['label'], properties_df['eccentricity'], color='purple')
axes[1, 1].set_title('Eccentricity')
axes[1, 1].set_xlabel('Label')
axes[1, 1].set_ylabel('Ratio')

# Adjust the layout
plt.tight_layout()

# Get the regions and their properties
regions = measure.regionprops(connected_components)

# Now, we have labeled each object with a cluster label
# We will visualize the results
fig, ax = plt.subplots(1, 3, figsize=(15, 5))

# Original Image
ax[0].imshow(image, cmap='gray')
ax[0].set_title('Original Image')
ax[0].axis('off')

# Binarized Image
ax[1].imshow(image_binary, cmap='gray')
ax[1].set_title('Binarized Image')
ax[1].axis('off')

# Labeled Image
ax[2].imshow(connected_components, cmap='nipy_spectral')
ax[2].set_title('Labeled Image')
ax[2].axis('off')

# Save the images and display them
binary_image_path = 'binary_image.jpg'
labeled_image_path = 'labeled_image.jpg'
image_binary = Image.fromarray((image_binary * 255).astype(np.uint8))
image_binary.save(binary_image_path)
connected_components_image = Image.fromarray((connected_components * 255 / connected_components.max()).astype(np.uint8))
connected_components_image.save(labeled_image_path)


properties_df

plt.show()


(properties, binary_image_path, labeled_image_path)
