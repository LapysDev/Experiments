# Import
from pathlib import Path
from PIL     import Image

import os
import sys

# Global
help_requested     = False
input_images       = []
input_images_size  = (0, 0)
input_with_stdin   = False
output_image       = None
output_image_size  = (0, 0)
output_name        = (get_output_name := lambda current_working_directory:
  current_working_directory.rpartition('\\')[-1]
  if current_working_directory == current_working_directory.rstrip().rstrip('\\') else
  get_output_name(current_working_directory.rstrip().rstrip('\\'))
)(os.getcwd())

tessellation_x = 0
tessellation_y = 0

# ... ->> Parse command-line arguments
assert __name__ == "__main__"

for (index, argument) in enumerate(sys.argv):
  if index == 0: continue # ->> ignore script name (or dummy `sys.argv[0]` command-line argument)

  argument       = argument.lstrip()
  argument_final = False
  argument_match = False

  # ->> Match `argument` against valueless flags
  for flag in ["-h", "--help", "-o", "--output"]:
    if argument.startswith(flag):
      argument = argument.removeprefix(flag).lstrip()

      if argument:
        if argument and '=' == argument[0] and flag not in ["-f", "--file", "-o", "--output"]:
          raise ValueError("Unexpected value `" + argument[1:].replace('`', "\\`") + "` for `" + flag + "` flag")

        argument = flag + argument
        break

      argument_match = True

      match flag:
        case "-h" | "--help":
          help_requested = True

        case "-o" | "--output":
          if index != len(sys.argv) - 2:
            raise ValueError("Expected `" + flag + "` as penultimate argument; prefer the format `[flags...|inputs...] " + flag + " [output-name]` or `[flags...|inputs...] " + flag + "=[output-name]` instead")

          argument_final = True
          output_name    = sys.argv[index + 1]
      break

  if argument_final: break
  if argument_match: continue

  # ->> Match `argument` against valued flags
  for flag in ["-f", "--file", "-o", "--output"]:
    if argument.startswith(flag):
      argument = argument.removeprefix(flag).lstrip()

      if '=' not in argument: raise ValueError("Expected value for `" + flag + "` flag")
      if '=' != argument[0] : raise ValueError("Invalid syntax for `" + flag + "` flag; suggest the `" + "--"[flag[1] != '-':] + "flag=value` format instead")

      argument       = argument[1:]
      argument_match = True

      match flag:
        case "-f" | "--file"  : input_images.append(argument)
        case "-o" | "--output": output_name = argument
      break

  if argument_final: break
  if argument_match: continue

  # ->> Optionally disallow image inputs via the command-line
  if input_with_stdin:
    raise LookupError("Unexpected " + ("argument" if argument[0] != '-' else "flag") + ": `" + argument.replace('`', "\\`") + '`')

  argument = sys.argv[index] # ->> expects only input image file paths

  if os.path.normpath("fakepath/" + argument).startswith("fakepath"): input_images.append(argument)
  else: raise ValueError("Invalid image file path `" + argument.replace('`', "\\`") + "` specified")

# ... ->> Validate (possibly modified) `output_name`
if '.' not in output_name:
  output_name += '.'

if not output_name.rpartition('.')[-1]:
  output_name += "png"

if not os.path.normpath("fakepath/" + output_name).startswith("fakepath"):
  raise ValueError("Invalid value `" + argument.replace('`', "\\`") + "` for `" + flag + "` flag")

# ... ->> Specify `input_images` via the standard input stream
if input_with_stdin:
  input_image   = ""
  input_pending = True

  print("Specify image file path: ", end="")

  while True:
    for input_image in iter(input, ""):
      input_image = input_image.lstrip('\n')

      if input_pending:
        print("add another image? [Y / N]: ", end="")

        input_images.append(input_image)
        input_pending = not input_pending

      else:
        match input_image.strip():
          case 'N' | 'n':
            break

          case 'Y' | 'y':
            print("add image file path: ", end="")
            input_pending = not input_pending

          case _:
            print("specify `Y` (for \"Yes\") or `N` (for \"No\") to add another image or quit the program")

    if input_image == 'N' or input_image == 'n':
      break

# ... ->> Help log
if help_requested:
  print("Concatenate specified images into a single bitmap\n")
  print('\t' + sys.argv[0] + " --output=output_name" + ("" if input_with_stdin else " input_image_path [input_image_path...]"))

else:
  # ... ->> Parse (and validate) `input_images` to static paths ie: no wildcards and such
  input_images.append(None)

  for input_image in input_images:
    input_images = input_images[1:]

    if input_image == None:
      break

    input_image

    for input_image in list(Path(input_image).glob('*')):
      if not (input_image.is_file() and os.path.exists(str(input_image))):
        raise ValueError("Invalid image file path `" + str(input_image).replace('`', "\\`") + "` specified")

      input_images.append(input_image)

    else:
      input_images.append(input_image)

  if len(input_images) == 0:
    raise RuntimeError("Expected specified images to concatenate")

  # ...
  for (index, input_image) in enumerate(input_images):
    input_image         = Image.open(input_image)
    input_image         = input_image.convert("RGBA") if input_image.format != "PNG" else input_image
    input_images[index] = input_image
    input_images_size   = input_image.size

    output_image_size = (max(input_image.width, output_image_size[0]), input_image.height + output_image_size[1])

  # if not all(input_image.size == input_images_size for input_image in input_images):
  #   raise ValueError("Expected specified images to be of the same size or dimensions (height and width)")

  output_image = Image.new("RGBA", output_image_size, color=(0x00, 0x00, 0x00))

  for input_image in input_images:
    output_image.paste(input_image, (int((output_image.width - input_image.width) / 2.0), tessellation_y))
    tessellation_y += input_image.height

  if Path(output_name).is_file() and os.path.exists(output_name):
    prompted = False

    while True:
      match input("" if prompted else "The file \"" + output_name.replace('"', "\\\"") + "\" already exists; are you sure you want to overwrite it? [Y / N]: "):
        case 'N' | 'n':
          sys.exit(0x1) # --> EXIT_FAILURE

        case 'Y' | 'y':
          break

        case _:
          prompted = True
          print("specify `Y` (for \"Yes\") or `N` (for \"No\") to add another image or quit the program")


  output_image.save(output_name, output_name.rpartition('.')[-1].upper())

# ...
sys.exit(0x0) # --> EXIT_SUCCESS
