from PIL import Image

def is_neighboring_pixels_same(img, x, y):
    width, height = img.size
    pixel = img.getpixel((x, y))

    # Define the neighbors' coordinates (N, E, S, W)
    neighbors = [
        (x, y - 1),  # North
        (x + 1, y),  # East
        (x, y + 1),  # South
        (x - 1, y)   # West
    ]

    for nx, ny in neighbors:
        if 0 <= nx < width and 0 <= ny < height:
            if img.getpixel((nx, ny)) != pixel:
                return False
    return True

def process_image(input_image_path, output_image_path):
    img = Image.open(input_image_path)
    img = img.convert('RGB')
    width, height = img.size

    output_img = Image.new('RGB', (width, height), (0, 0, 0))
    pixels = output_img.load()

    for y in range(height):
        for x in range(width):
            if is_neighboring_pixels_same(img, x, y):
                pixels[x, y] = img.getpixel((x, y))
            else:
                pixels[x, y] = (0, 0, 0)

    output_img.save(output_image_path)

if __name__ == "__main__":
    input_image_path = "input.bmp"
    output_image_path = "inputchanged.bmp"
    process_image(input_image_path, output_image_path)

print("gdfg")
