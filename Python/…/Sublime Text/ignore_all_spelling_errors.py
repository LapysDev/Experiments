import sublime, sublime_plugin

class IgnoreAllSpellingErrors(sublime_plugin.TextCommand):
  def run(self, edit):
    regions = []
    while True:
      self.view.run_command("next_misspelling")
      if self.view.sel()[0] not in regions:
        regions.append(self.view.sel()[0])
        for word in [self.view.substr(s) for s in self.view.sel()]:
          self.view.run_command("ignore_word", {"word": word})
      else:
        break

    self.view.sel().clear()
