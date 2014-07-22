################################
####### GAME MECHANICS #########
################################

def makeDeck(numCards=40):
  """
  Returns array of numCards integers in the range [0-13].
  """
  from random import randrange
  return [randrange(14) for i in range(numCards)]

def randomStrategy(percent=50):
  """
  Default strategy: hit 50% of the time
  """
  from random import randrange
  while True:
    yield (randrange(1, 100) <= percent)

def simulateTurn(deck, humanHits):
  """
  Applies given strategy to given deck for a single turn.
  Returns (number of the winning player, resulting deck)
  NOTE: if tie, number of winning player is -1
  """
  # TODO: generalize this for AI strategy and n players

  # 1. draw cards
  score0 = deck.pop(0)
  score1 = deck.pop(0)

  # 2. human player: hit or stay
  if humanHits:
    # if hit, draw a card
    score0 = (score0 + deck.pop(0)) % 14

  # 3. AI player: hit or stay
  if score0 > score1:
    # strategy: hit if human player has higher score
    score1 = (score1 + deck.pop(0)) % 14

  # 4. determine winner, tie is -1
  winner = -1
  if score0 > score1:
    winner = 0
  elif score0 < score1:
    winner = 1
  return winner, deck

def simulateGame(deck=None, strategy=None):
  """
  Returns total wins for each player.
  Given optional strategy, which is an iterator of booleans representing player decisions.
  Generates random 40 card deck if no deck is given.
  Generates random strategy if no strategy is given.
  """
  if deck is None:
    deck = makeDeck()
  else:
    # copy deck so we don't mutate it
    deck = deck[:]
  if strategy is None:
    strategy = randomStrategy()

  # each iteration is a single turn of the game
  wins = [0] * 2 # currently fixed at 2 players
  while len(deck) >= 4:
    try:
      winner, deck = simulateTurn(deck, next(strategy))
      if winner >= 0:
        # tally turn wins
        wins[winner] += 1
    except StopIteration:
      raise Exception("Strategy did not last for a complete game.")

  # return array of wins => wins[0] is human, wins[1] is AI
  return wins

def determineWinner(wins):
  """
  Returns (index of winning player, total wins of that player).
  NOTE: index of winning player is -1 in the event of a tie.
  """
  maxWins = max(wins)
  winners = [i for i, j in enumerate(wins) if j == maxWins]
  if len(winners) != 1:
    # multiple 'winners' means tie
    return -1, maxWins
  else:
    return winners[0], maxWins


###########################
####### SOLUTIONS #########
###########################

# exponential space and time, 2**n
def naiveStrategy(deck):
  """
  Returns a winning series of decisions, if one exists, else None.
  """
  def helper(deck):

    # base case: if deck has too few cards, strategy is degenerate
    strategy, wins = [], [0, 0]
    if len(deck) >= 4:

      # 2 decisions: hit or stay. calculate turn outcome of each.
      hitWinner, hitDeck = simulateTurn(deck[:], True)
      stayWinner, stayDeck = simulateTurn(deck[:], False)

      # now calculate game outcome of rest of turns
      hitStrategy, hitWins = helper(hitDeck)
      stayStrategy, stayWins = helper(stayDeck)

      # add this turn's outcome into current score for each decision
      if hitWinner >= 0: # ignore ties
        hitWins[hitWinner] += 1
      if stayWinner >= 0: # ignore ties
        stayWins[stayWinner] += 1

      # now, given the results for hitting and staying,
      # pick the strategy which leads to a win, if there is one
      # NOTE: a strategy of None means that deck has no win for the human player
      if (hitStrategy is not None) and \
      (determineWinner(hitWins)[0] == 0):
        strategy = [True] + hitStrategy
        wins = hitWins
      elif (stayStrategy is not None) and \
      (determineWinner(stayWins)[0] == 0):
        strategy = [False] + stayStrategy
        wins = stayWins
      else:
        strategy = None

    return strategy, wins

  # invoke helper, then return winning strategy
  strategy, wins = helper(deck)
  return strategy

def optimalStrategy():
  # TODO: same basic idea as naive except memoized and iterative?
  pass


#############################
########## TESTING ##########
#############################

for i in range(10):
  deck = makeDeck(50)
  strat = naiveStrategy(deck)
  if strat is None:
    print("no winning strategy")
  else:
    print("sample game outcome with naive strategy: ", simulateGame(deck, iter(strat)))
