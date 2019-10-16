# search.py
# ---------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


"""
In search.py, you will implement generic search algorithms which are called by
Pacman agents (in searchAgents.py).
"""

import util

class SearchProblem:
    """
    This class outlines the structure of a search problem, but doesn't implement
    any of the methods (in object-oriented terminology: an abstract class).

    You do not need to change anything in this class, ever.
    """

    def getStartState(self):
        """
        Returns the start state for the search problem.
        """
        util.raiseNotDefined()

    def isGoalState(self, state):
        """
          state: Search state

        Returns True if and only if the state is a valid goal state.
        """
        util.raiseNotDefined()

    def getSuccessors(self, state):
        """
          state: Search state

        For a given state, this should return a list of triples, (successor,
        action, stepCost), where 'successor' is a successor to the current
        state, 'action' is the action required to get there, and 'stepCost' is
        the incremental cost of expanding to that successor.
        """
        util.raiseNotDefined()

    def getCostOfActions(self, actions):
        """
         actions: A list of actions to take

        This method returns the total cost of a particular sequence of actions.
        The sequence must be composed of legal moves.
        """
        util.raiseNotDefined()


def tinyMazeSearch(problem):
    """
    Returns a sequence of moves that solves tinyMaze.  For any other maze, the
    sequence of moves will be incorrect, so only use this for tinyMaze.
    """
    from game import Directions
    s = Directions.SOUTH
    w = Directions.WEST
    return  [s, s, w, s, w, w, s, w]

def depthFirstSearch(problem):
    """
    Search the deepest nodes in the search tree first.

    Your search algorithm needs to return a list of actions that reaches the
    goal. Make sure to implement a graph search algorithm.

    To get started, you might want to try some of these simple commands to
    understand the search problem that is being passed in:

    print("Start:", problem.getStartState())
    print("Is the start a goal?", problem.isGoalState(problem.getStartState()))
    print("Start's successors:", problem.getSuccessors(problem.getStartState()))
    """

    Q = util.Stack()
    visited = []
    actions = []
    myDfs(problem.getStartState(), problem, Q, visited)
    check_path(visited, problem, actions)
    actions.reverse()
    print("Start:", problem.getStartState())
    print("Is the start a goal?", problem.isGoalState(problem.getStartState()))
    print("Start's successors:", problem.getSuccessors(problem.getStartState()))

    return actions

def myDfs(state, problem, stack, visited):

    if state is None:
        return None
    else:
        if not is_visited(state, visited):
            visited.append(state)
            if problem.isGoalState(state):
                return visited #state
            elif len(problem.getSuccessors(state)) == 0:
                if stack.isEmpty():
                    return None
                else:
                    return myDfs(stack.pop(), problem, stack, visited) # check next state
            else:
                for x in problem.getSuccessors(state):
                    if not is_visited(x[0], visited):
                        stack.push(x[0])
                return myDfs(stack.pop(), problem, stack, visited) # check next state
        else:
            return myDfs(stack.pop(), problem, stack, visited)


def check_path(path, father_son_actions, actions):
    x = len(path) - 1
    y = len(path) - 2
    #{'Parent': A, 'Childs_triple': [((1,2), North, 1), ((2,3), Sud, 1)], 'Child': [(1,2), (2,4)]}
    #[parent = (1,2), child_triple = [((1,2), North, 1), ((2,3), Sud, 1)], child = [(1,2), (2,4)]]
    while y > -1:
        succ = []
        if (path[y], path[x], _) in father_son_actions:
           actions.append(father_son_actions)
           print("ciao")
        if path[x] not in succ:
            tmp = y
            y = y - 1
            path.pop(tmp)
            x = x - 1
        else:
            x = y
            y = y - 1
    return path

'''def check_path(lastState, actions, relationship):
    state = lastState
    element = relationship.pop()
    print("element", element['Childs'])
    print("?", state in element['Childs'])
    while state in element['Childs']:
    #{'Parent': (1,2), 'Childs_triple': [((1,2), 'North', 1), ((2,3), 'Sud', 1)], 'Childs': [(1,2), (2,4)]}
    #[parent = (1,2), child_triple = [((1,2), North, 1), ((2,3), Sud, 1)], child = [(1,2), (2,4)]]
        index = element['Childs'].index(state) #per (1,2) sarà 0
        child_triple = element['Childs_triple']
        action = child_triple[index][1]
        actions.append(action)
        print(actions)
        parent = element['Parent']
        state = parent
    return actions
    x = len(visited) - 1
    y = len(visited) -2
    while y > -1:
        succ = []
        if
        for i in child(path[y]):
            succ.append(i[0])
            if i[0] == path[x]:
                actions.append(i[1])
        if path[x] not in succ:
            tmp = y
            y = y - 1
            path.pop(tmp)
            x = x - 1
        else:
            x = y
            y = y - 1
    return path'''
def is_visited(state, visited):
    return state in visited

def breadthFirstSearch(problem):
    """Search the shallowest nodes in the search tree first."""
    startState = problem.getStartState()
    queue = util.Queue()
    visited = []
    actions = []
    relationship = []
    father_son_action = []
    myBfs(startState, problem, queue, visited, relationship)
    print("ultimo visited, goal", visited[len(visited) - 1])
    print("rel", relationship)
    print("visited", visited)
    print("relrel", relationship)
    for x in relationship:
        for y in x['Childs']:
            index = x['Childs'].index(y)
            print("index", index)
            print("child_triple", x['Childs_actions'])
            action = x['Childs_actions'][index][1]
            print("action", action)
            father_son_action.append((x['Father'], y, action)) # tutte le possibili coppie padre_figlio
    check_path(visited[len(visited) - 1], actions, relationship)
    print("father_son_action", father_son_action)
    actions.reverse()
    print("right actions ", actions)

    return actions

def myBfs(startState, problem, queue, visited, relationship):
    queue.push(startState)
    while not queue.isEmpty():
        state = queue.pop()
        visited.append(state)
        if problem.isGoalState(state):
            return visited
        successors = problem.getSuccessors(state)
        childs = []
        for x in successors:
            childs.append(x[0])
            if not is_visited(x[0], visited):
                queue.push(x[0])
        relationship.append({'Father': state, 'Childs_actions': successors, 'Childs': childs})
    return None


def uniformCostSearch(problem):
    #nieuwe: cost = number of steps - number of food items + 1000 if ghost on path
    startState = problem.getStartState()
    pq = util.PriorityQueue()
    visited = []
    actions = []
    myUcs(startState, problem, pq, visited)
    check_path(visited, problem, actions)
    actions.reverse()
    print("actions ", actions)
    return actions

def myUcs(startState, problem, pq, visited):
    pq.push(startState, 0)
    while not pq.isEmpty():
        state = pq.pop()
        visited.append(state)
        if problem.isGoalState(state):
            return visited
        if len(problem.getSuccessors(state)) > 0:
            for x in problem.getSuccessors(state):
                if not is_visited(x[0], visited):
                    pq.push(x[0], x[2])

def nullHeuristic(state, problem=None):
    """
    A heuristic function estimates the cost from the current state to the nearest
    goal in the provided SearchProblem.  This heuristic is trivial.
    """
    return 0

def aStarSearch(problem, heuristic=nullHeuristic):
    """Search the node that has the lowest combined cost and heuristic first."""
    "*** YOUR CODE HERE ***"
    util.raiseNotDefined()


# Abbreviations
bfs = breadthFirstSearch
dfs = depthFirstSearch
astar = aStarSearch
ucs = uniformCostSearch
