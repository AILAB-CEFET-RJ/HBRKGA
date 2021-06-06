from hbrkga import hbrkga

# params = [
#   (1000, 2000),
#   (2000, 4000),
#   (4000, 6000),
#   (1E-6, 1E-1),
#   (0, 1E-3),
# ]
# 
# ga_params = {
#   'eg': 5,
#   'n': 100,
#   'p': 1000,
#   'pe': 0.2,
#   'pm': 0.1,
#   'rhoe': 0.7,
#   'k': 1,
#   'maxT': 1,
#   'rngSeed': 0,
#   'generation': 0,
#   'xIntvl': 100,
#   'xNumber': 2,
#   'maxGens': 1000,
# }

params = [
  (100, 200),
  (200, 400),
  (400, 600),
  (1E-6, 1E-1),
  (0, 1E-3),
]

ga_params = {
  'eg': 5,
  'n': 100,
  'p': 1000,
  'pe': 0.2,
  'pm': 0.1,
  'rhoe': 0.7,
  'k': 1,
  'maxT': 1,
  'rngSeed': 0,
  'generation': 0,
  'xIntvl': 100,
  'xNumber': 2,
  'maxGens': 1,
}
hbrkga(params, ga_params)