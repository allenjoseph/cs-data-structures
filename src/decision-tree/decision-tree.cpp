#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <filesystem>
#include <cmath>
#include <map>
#include <set>
#include <array>

using namespace std;
using matrix = vector<vector<string>>;

class Condition
{
private:
    int k;
    string e;

public:
    Condition() {}

    Condition(int kval, string eval)
    {
        this->k = kval;
        this->e = eval;
    }

    ~Condition() {}

    int col()
    {
        return this->k;
    }

    string val()
    {
        return this->e;
    }

    bool isNumber(double *num)
    {
        try
        {
            *num = stod(this->e);
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    void printCondition(vector<string> headers)
    {
        cout << "Is ";
        cout << headers[this->k];

        double numVal;
        bool valIsNumber = this->isNumber(&numVal);
        if (valIsNumber)
        {
            cout << " >= ";
        }
        else
        {
            cout << " == ";
        }
        cout << this->e;
        cout << " ?" << endl;
    }
};

class DecisionNode
{
private:
    Condition* c;
    DecisionNode* l;
    DecisionNode* r;
    bool leaf = false;
    map<string, int> predictions;
    vector<string> headers;

public:
    DecisionNode() {}

    DecisionNode(vector<string> headers, Condition* c, DecisionNode* l, DecisionNode* r) {
        this->headers = headers;
        this->c = c;
        this->l = l;
        this->r = r;
    }

    DecisionNode(vector<string> headers, map<string, int> predictions) {
        this->headers = headers;
        this->leaf = true;
        this->predictions = predictions;
    }

    ~DecisionNode() {}

    bool isLeaf() {
        return this->leaf;
    }

    DecisionNode* getLeftNode() {
        return this->l;
    }

    DecisionNode* getRightNode() {
        return this->r;
    }

    bool compareRow(vector<string> row) {
        double numVal;
        return this->c->isNumber(&numVal)
               ? stod(row[this->c->col()]) >= numVal
               : row[this->c->col()] == this->c->val();
    }

    void printCondition() {
        if (this->leaf) {
            return;
        }

        this->c->printCondition(this->headers);
    }

    void printPredictions()
    {
        if (!this->leaf) {
            return;
        }

        map<string, int>::iterator it;
        cout << "Predict: { ";
        for (it = this->predictions.begin(); it != this->predictions.end(); ++it)
        {
            cout << it->first;
            cout << ": ";
            cout << it->second;
            cout << ", ";
        }
        cout << " }" << endl;
    }

    map<string, int> getPredictions() {
        return this->predictions;
    }
};

matrix readFile(string filename)
{
    matrix rows;

    string line;
    ifstream reader(filename);
    char csvDelimiter = ',';

    if (reader)
        while (!reader.eof())
        {
            getline(reader, line);
            vector<string> row;

            size_t pos = line.find(csvDelimiter);
            size_t initialPos = 0;
            string column;

            while (pos != std::string::npos)
            {
                column = line.substr(initialPos, pos - initialPos);
                row.push_back(column);
                initialPos = pos + 1;
                pos = line.find(csvDelimiter, initialPos);
            }

            // Add the last one
            column = line.substr(initialPos, min(pos, line.size()) - initialPos + 1);
            row.push_back(column);

            rows.push_back(row);
        }

    if (!reader)
        cout << "No pudimos abrir el archivo " << filename << endl;

    reader.close();

    return rows;
}

map<string, int> countLabels(matrix rows)
{
    map<string, int> labelCounts;

    for (vector<string> row : rows)
    {
        string label = row.back(); // the label is the last column
        map<string, int>::iterator itr = labelCounts.find(label);
        if (itr != labelCounts.end()) {
            itr->second = (itr->second) + 1;
        } else {
            labelCounts.insert(pair<string, int>(label,1));
        }
    }

    return labelCounts;
}

double giniImpurity(matrix rows)
{
    double impurity = (double)1;
    map<string, int> labelCounts = countLabels(rows);

    map<string, int>::iterator it;
    for (it = labelCounts.begin(); it != labelCounts.end(); ++it)
    {
        double probability = it->second / (double)rows.size();
        impurity -= pow(probability,2);
    }

    return impurity;
}

double giniGain(double currentUncertainty, array<matrix, 2> branches) {

    double pLeftBranch = branches[0].size() / (double)(branches[0].size() + branches[1].size());
    double leftBranch = pLeftBranch * giniImpurity(branches[0]);
    double rightBranch = (1 - pLeftBranch) * giniImpurity(branches[1]);
    double gain = currentUncertainty - (leftBranch + rightBranch);

    return gain;
}

double informationEntropy(matrix rows)
{
    double entropy = (double)0;
    map<string, int> labelCounts = countLabels(rows);

    map<string, int>::iterator it;
    for (it = labelCounts.begin(); it != labelCounts.end(); ++it)
    {
        double probability = it->second / (double)rows.size();
        entropy += probability * log2(probability);
    }

    return -1 * entropy;
}

double informationGain(double currentUncertainty, array<matrix, 2> branches) {

    double pLeftBranch = branches[0].size() / (double)(branches[0].size() + branches[1].size());
    double leftBranch = pLeftBranch * informationEntropy(branches[0]);
    double rightBranch = (1 - pLeftBranch) * informationEntropy(branches[1]);
    double gain = currentUncertainty - (leftBranch + rightBranch);

    return gain;
}

array<matrix, 2> splitDataset(matrix rows, Condition *condition)
{
    array<matrix, 2> branches;

    double conditionVal;
    bool valIsNumber = condition->isNumber(&conditionVal);

    for (vector<string> row : rows)
    {
        bool isForleftBranch = valIsNumber
                                   ? stod(row[condition->col()]) >= conditionVal
                                   : row[condition->col()] == condition->val();

        if (isForleftBranch)
        {
            branches[0].push_back(row);
        }
        else
        {
            branches[1].push_back(row);
        }
    }

    return branches;
}

Condition *findBestSplit(matrix rows, double *bestGain) {
    double currentUncertainty = giniImpurity(rows);

    // double currentUncertainty = informationEntropy(rows);

    int features = rows[0].size() - 1;

    Condition *bestCondition = NULL;

    for (int i = 0; i < features; i++)
    {
        set<string> uniqueValues;
        for (vector<string> row : rows)
        {
            uniqueValues.insert(row[i]);
        }

        for (string val : uniqueValues)
        {
            Condition *condition = new Condition(i, val);
            auto branches = splitDataset(rows, condition);

            if (branches[0].size() == 0 || branches[1].size() == 0)
            {
                continue;
            };

            double gain = giniGain(currentUncertainty, branches);

            // double gain = informationGain(currentUncertainty, branches);

            if (gain >= *bestGain)
            {
                *bestGain = gain;
                bestCondition = condition;
            }
        }
    }

    return bestCondition;
}

DecisionNode* buildTree(matrix rows, vector<string> headers)
{
    double bestGain = 0;

    Condition *bestCondition = findBestSplit(rows, &bestGain);

    if (bestGain == 0)
    {
        return new DecisionNode(headers, countLabels(rows));
    }

    auto branches = splitDataset(rows, bestCondition);

    DecisionNode *leftBranch = buildTree(branches[0], headers);

    DecisionNode *rightBranch = buildTree(branches[1], headers);

    return new DecisionNode(headers, bestCondition, leftBranch, rightBranch);
}

void printTree(DecisionNode *node) {

    if (node->isLeaf()) {
        node->printPredictions();
        return;
    }

    node->printCondition();

    cout << "TRUE:" << endl;
    printTree(node->getLeftNode());

    cout << "FALSE:" << endl;
    printTree(node->getRightNode());
}

void printPredictions(vector<string> row, map<string, int> predictions)
{
    int sum = 0;
    map<string, int>::iterator it;
    for (it = predictions.begin(); it != predictions.end(); ++it) {
        sum += it->second;
    }

    cout << "Current: " << row.back() << ", Predict: { ";
    for (it = predictions.begin(); it != predictions.end(); ++it)
    {
        cout << it->first;
        cout << ": ";
        cout << (it->second / (double)sum) * 100;
        cout << "%, ";
    }
    cout << " }" << endl;
}

map<string, int> classify(vector<string> row, DecisionNode* node) {

    if (node->isLeaf()) {
        return node->getPredictions();
    }

    if (node->compareRow(row)) {
        return classify(row, node->getLeftNode());
    } else {
        return classify(row, node->getRightNode());
    }
}

int main()
{
    cout << "Decision Tree" << endl;
    cout << "= = = = = = = = = = = = = = = =" << endl;

    matrix rows = readFile("iris.txt");

    vector<string> headers = rows.front();
    rows.erase(rows.begin());

    size_t sizeTraining = floor(rows.size() * 0.7);
    matrix rowsTraining(rows.begin(), rows.begin() + sizeTraining);
    matrix rowsTesting(rows.begin() + sizeTraining, rows.end());

    DecisionNode *root = buildTree(rowsTraining, headers);

    cout << "Testing" << endl;
    cout << "= = = = = = = = = = = = = = = =" << endl;

    for (int i = 0; i < rowsTesting.size(); ++i) {
        printPredictions(rowsTesting[i], classify(rowsTesting[i], root));
    }

    return 0;
}