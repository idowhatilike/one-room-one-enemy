from argparse import ArgumentParser
from pathlib import Path

from PIL import Image


def removeBackground(source: Path , destination: Path , fadeSignature: bool = False):
    with Image.open(source) as original:
        image = original.convert("RGBA")

    pixels = image.load()
    background = pixels[0 , 0]
    removedCount = 0
    for y in range(image.height):
        for x in range(image.width):
            if pixels[x , y] == background:
                pixels[x , y] = (0 , 0 , 0 , 0)
                removedCount += 1

    if fadeSignature:
        # Chỉ giảm alpha vùng chữ ký để không làm nhòe sprite.
        signature = image.crop((10 , 10 , 100 , 60))
        signature.putalpha(signature.getchannel("A").point(lambda alpha: round(alpha * 0.2)))
        image.paste(signature , (10 , 10))

    image.save(destination)
    return image.size , background , removedCount


if __name__ == "__main__":
    parser = ArgumentParser()
    parser.add_argument("sprite" , nargs="?" , default="reze")
    args = parser.parse_args()
    projectRoot = Path(__file__).resolve().parent.parent
    dimensions , background , removedCount = removeBackground(
        projectRoot / f"assets/{args.sprite}_raw.png" , projectRoot / f"assets/{args.sprite}_idle.png" , args.sprite == "reze"
    )
    print(f"Dimensions: {dimensions}; background: {background}; removed: {removedCount}")
