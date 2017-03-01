var path = require('path');
global.__randardir = path.normalize('..');

var args    = process.argv.slice(2);
var goals   = [];
var options = { };

args.forEach(function(arg) {
    if (arg === 'full=yes') {
        options.full = true;
    }

    else {
        goals.push(arg);
    }
});

function getBuildGoal(goalName) {
    return require(path.join(__dirname, 'build-goals', goalName));
}

function buildGoal(goalName) {
    var goal = possibleGoals[goalName];
    if (!goal) {
        return;
    }

    goal.build(options, function(err) {
        if (err) {
            console.error(err);
        }
    });
}

var possibleGoals = {
    ui     : getBuildGoal('ui'),
    engine : getBuildGoal('engine')
};

(goals.length ? goals : Object.keys(possibleGoals)).forEach(buildGoal);
