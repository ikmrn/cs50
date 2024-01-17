# Simulate a sports tournament

import csv
import random
import sys

# Number of simulations to run
N = 10


def main():
    """Main function"""
    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    # TODO: Read teams into memory from file
    with open(sys.argv[1], encoding="UTF-8") as file:
        reader = csv.DictReader(file)
        for team in reader:
            team["rating"] = int(team["rating"])
            teams.append(team)

    counts = {}
    # TODO: Simulate N tournaments and keep track of win counts
    for _ in range(N):
        name = simulate_tournament(teams)
        if name in counts:
            counts[name] += 1
        else:
            counts[name] = 1
    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1: dict, team2: dict) -> bool:
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams: list) -> list:
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams: list) -> str:
    """Simulate a tournament. Return name of winning team."""
    # Base case: If there are only two teams, simulate the final round
    if len(teams) == 1:
        return teams[0]["team"]  # Return the winner directly

    # Simulate the current round
    winners = simulate_round(teams)
    return simulate_tournament(winners)


if __name__ == "__main__":
    main()
