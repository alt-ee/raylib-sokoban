# Sokoban player in Raylib

# Steps to working program:
- [ ] Open .txt file containing levels
- [ ] Split file into individual levels
- [x] Parse each level into array of enums (i.e. play grid)
- [ ] Level select
  maybe before parsing levels - only parse the selected level?
  what is the tradeoff of parsing levels when needed vs parsing all and storing in memory?
  - potential compromise - load all level strings, then parse into Level objects as needed. 
- [x] Draw level
- [.] Controls
  - [ ] Restart button
  - [ ] Next/previous level
- [x] Player-box interaction
- [ ] Detect victory state

- [ ] UI
  - [ ] Move count
  - [ ] Level number
  - [ ]
