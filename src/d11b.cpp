#include <iostream>
#include <fstream>
#include <functional>
#include <vector>
#include <memory>

class Monkey
{
public:
    std::function<size_t()> operation;
    std::function<bool()>   test;
    std::vector<size_t> items;
    size_t toMonkeyIfTrue, toMonkeyIfFalse;
    size_t itemsInspected = 0;

    Monkey(const std::vector<size_t> itemList, 
           const std::string &op, const std::string &tst, 
           size_t monkeyIfTrue, size_t monkeyIfFalse)
        : items(itemList)
        , toMonkeyIfTrue(monkeyIfTrue)
        , toMonkeyIfFalse(monkeyIfFalse)
    {
        if (op.substr(25) == "old")
            operation = [&]() { return items[0] * items[0]; };
        else if (op[23] == '*') {
            operationNumber = stoi(op.substr(25));
            operation = [&]() { return items[0] * operationNumber; };
        }
        else if (op[23] == '+') {
            operationNumber = stoi(op.substr(25));
            operation = [&]() { return items[0] + operationNumber; };
        }
        
        testNumber = stoi(tst.substr(21));
        test = [&]() { return items[0] % testNumber == 0; };
    }

    size_t monkeyToThrowTo() const
    {
        return test() ? toMonkeyIfTrue : toMonkeyIfFalse;
    }

private:
    size_t operationNumber = 0;
    size_t testNumber = 0;
};

void playRound(std::vector<std::unique_ptr<Monkey>> &monkeys, size_t mod)
{
    for (auto& monkey : monkeys) {
        monkey->itemsInspected += monkey->items.size();

        while (monkey->items.size() > 0) {
            monkey->items[0] = monkey->operation();
            monkey->items[0] = monkey->items[0] % mod;
            monkeys[monkey->monkeyToThrowTo()]->items.push_back(monkey->items[0]);
            monkey->items.erase(monkey->items.begin());
        }
    }
}

int main()
{
    std::ifstream monkeyInformation("inputs/d11.txt");
    std::string line, operation, test;
    std::vector<size_t> initialItems;
    std::vector<std::unique_ptr<Monkey>> monkeys;
    size_t mod = 1;

    while (getline(monkeyInformation, line)) {
        if (line.empty()) continue;
        initialItems.clear();

        std::string itemsList;
        getline(monkeyInformation, itemsList);
        itemsList = itemsList.substr(18);
        size_t commaPos = itemsList.find(",");
        while (commaPos != std::string::npos) {
            initialItems.push_back(stoi(itemsList.substr(0, commaPos)));
            itemsList = itemsList.substr(commaPos + 2);
            commaPos = itemsList.find(",");
        }
        initialItems.push_back(stoi(itemsList.substr(0, commaPos)));

        getline(monkeyInformation, operation);
        getline(monkeyInformation, test);
        mod *= stoi(test.substr(21));

        getline(monkeyInformation, line);
        size_t monkeyIfTrue = stoi(line.substr(29));
        getline(monkeyInformation, line);
        size_t monkeyIfFalse = stoi(line.substr(30));

        std::unique_ptr<Monkey> monkey = std::make_unique<Monkey>(
            initialItems,
            operation,
            test,
            monkeyIfTrue,
            monkeyIfFalse 
        );

        monkeys.push_back(std::move(monkey));
    }
    
    for (size_t i = 0; i < 10'000; i++)
        playRound(monkeys, mod);

    std::vector<size_t> itemsInspected(monkeys.size());
    for (size_t i = 0; i < monkeys.size(); i++) 
        itemsInspected[i] = monkeys[i]->itemsInspected;

    size_t top2[2] = {};
    for (auto num : itemsInspected) {
        for (size_t i = 0; i < 2; i++) {
            if (num > top2[i]) {
                for (size_t j = 2; j > i; j--) 
                    top2[j] = top2[j - 1];

                top2[i] = num;
                break;
            }
        }
    }
    
    std::cout << top2[0]*top2[1] << "\n";
}