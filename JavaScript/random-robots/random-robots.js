const DIRECTIONS = ["DOWN", "LEFT", "RIGHT", "UP"],
    ROBOTS = [];

class Robot { constructor() { this.directions = [] } };
function getRandomDirection() { return DIRECTIONS[(Math.random() * DIRECTIONS.length) | 0] }

iterationCount = 1e3;
iteration = iterationCount;

while (iteration) { ROBOTS.push(new Robot); iteration -= 1 }

iteration = iterationCount;

while (iteration) {
    ROBOTS.forEach(robot => robot.directions.push(getRandomDirection()));
    iteration -= 1
}
