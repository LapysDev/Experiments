import os
import sys

# Global
input_images     = []
input_with_stdin = False
help_requested   = False
output_name      = (get_output_name := lambda current_working_directory:
  current_working_directory.rpartition('\\')[-1]
  if current_working_directory == current_working_directory.rstrip().rstrip('\\') else
  get_output_name(current_working_directory.rstrip().rstrip('\\'))
)(os.getcwd())

# ... ->> Get command-line arguments
assert __name__ == "__main__"

for (index, argument) in enumerate(sys.argv):
  if index == 0: continue

  argument       = argument.lstrip()
  argument_match = False

  # ->> Match `argument` against valueless flags
  for flag in ["-h", "--help"]:
    if argument.startswith(flag):
      if '=' in argument: raise ValueError("Unexpected value `" + argument.partition('=')[-1].replace('`', "\\`") + "` for `" + flag + "` flag")
      if len(argument.removeprefix(flag).lstrip()) != 0: continue

      argument_match = True

      match flag:
        case "-h" | "--help":
          help_requested = True
      break
  if argument_match: continue

  # ->> Match `argument` against valued flags
  for flag in ["-f", "--file", "-o", "--output"]:
    if argument.startswith(flag):
      argument = argument.removeprefix(flag).lstrip()

      if '=' not in argument:
        if flag != "-o" and flag != "--output" : raise ValueError("Expected value for `" + flag + "` flag")
        if index != len(sys.argv) - 2: raise ValueError("Expected `" + flag + "` as penultimate argument; prefer the format `[flags...|inputs...] -o [output-name]` or `[flags...|inputs...] -o=[output-name]` instead")

        argument_match = True
        output_name    = sys.argv[index + 1]

        break

      if argument[0] != '=':
        raise ValueError("Invalid syntax for `" + flag + "` flag; suggest the `" + ('-' if flag[1] != '-' else "--") + "flag=value` format instead")

      argument       = argument.partition('=')[-1]
      argument_match = True

      match flag:
        case "-f" | "--file":
          input_images.append(argument)

        case "-o" | "--output":
          output_name = argument
      break
  if argument_match: continue

  # ->> Optionally disallow image inputs via the command-line
  if input_with_stdin:
    raise LookupError("Unexpected " + ("argument" if argument[0] != '-' else "flag") + ": `" + argument + '`')

  argument = sys.argv[index] # ->> expects only input image file paths

  if not os.path.normpath("fakepath/" + argument).startswith("fakepath"):
    raise ValueError("Invalid image file path `" + argument + "` specified")

  input_images.append(argument)

# ...
if not os.path.normpath("fakepath/" + output_name).startswith("fakepath"): # ->> validate `output_name`
  raise ValueError("Invalid value `" + argument.replace('`', "\\`") + "` for `" + flag + "` flag")

print("Help requested:" + str(help_requested))
print("Output name: \"" + output_name.replace('"', "\\\"") + '"')
print("Input images: " + str(input_images))

if help_requested:
  print("")
  sys.exit()
