const { execSync, spawn } = require('child_process');
const fs = require('fs');
const inquirer = require('inquirer');

async function main() {

    const modules = fs.readdirSync('./src');
    const answer1 = await promptList(modules, 'Choose a module');

    const exerciseSet = fs.readdirSync(`./src/${answer1.choice}`);
    const answer2 = await promptList(exerciseSet, 'Choose an exercise');

    const exercisePath = `./src/${answer1.choice}/${answer2.choice}`;
    execSync(`g++ -o ${exercisePath}.out ${exercisePath}`);
    spawn(`./${exercisePath}.out`, { stdio: 'inherit' });
}

main();

//#region helper functions

async function promptList(choices, message) {
    return inquirer.prompt([
        {
            type: 'list',
            name: 'choice',
            message: message || 'Choose and option',
            choices: choices || []
        }
    ]);
}

//#endregion