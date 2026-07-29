import os
import exifread
import csv

# === CONFIG ===
IMAGES_FOLDER = "assets/images/"  # Folder with geotagged JPEGs
OUTPUT_CSV = "image_gps_output.csv"

# Convert EXIF GPS format to decimal degrees
def dms_to_decimal(dms, ref):
    degrees = float(dms[0].num) / dms[0].den
    minutes = float(dms[1].num) / dms[1].den
    seconds = float(dms[2].num) / dms[2].den
    decimal = degrees + (minutes / 60.0) + (seconds / 3600.0)
    if ref in ['S', 'W']:
        decimal = -decimal
    return decimal

# Read GPS from image
def extract_gps(filepath):
    with open(filepath, 'rb') as f:
        tags = exifread.process_file(f, details=False)
        try:
            lat = dms_to_decimal(tags['GPS GPSLatitude'].values, tags['GPS GPSLatitudeRef'].values)
            lon = dms_to_decimal(tags['GPS GPSLongitude'].values, tags['GPS GPSLongitudeRef'].values)
            alt = float(tags['GPS GPSAltitude'].values[0].num) / tags['GPS GPSAltitude'].values[0].den
            return lat, lon, alt
        except KeyError:
            return None, None, None

# Process images
results = []
for img_file in sorted(os.listdir(IMAGES_FOLDER)):
    if img_file.lower().endswith('.jpg'):
        path = os.path.join(IMAGES_FOLDER, img_file)
        lat, lon, alt = extract_gps(path)
        results.append([img_file, lat, lon, alt])

# Save to CSV
with open(OUTPUT_CSV, 'w', newline='') as csvfile:
    writer = csv.writer(csvfile)
    writer.writerow(['image', 'latitude', 'longitude', 'altitude'])
    writer.writerows(results)

print(f"✅ GPS data extracted and saved to: {OUTPUT_CSV}")

