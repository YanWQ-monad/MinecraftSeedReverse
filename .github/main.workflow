workflow "Build & Test" {
  on = "push"
  resolves = ["actions/action-builder/shell@master-1"]
}

action "actions/action-builder/shell@master" {
  uses = "actions/action-builder/shell@master"
  runs = "make"
  args = "build"
}

action "actions/action-builder/shell@master-1" {
  uses = "actions/action-builder/shell@master"
  needs = ["actions/action-builder/shell@master"]
  runs = "make"
  args = "test"
}
