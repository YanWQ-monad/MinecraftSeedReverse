workflow "Build & Test" {
  on = "push"
  resolves = ["Test"]
}

action "Build" {
  uses = "actions/action-builder/shell@master"
  runs = "make"
  args = "build"
}

action "Test" {
  uses = "actions/action-builder/shell@master"
  runs = "make"
  args = "test"
  needs = ["Build"]
}
