//random float in range 0.0..1.0
float randomFloat(){
    return (float)rand()/RAND_MAX;
}

class qlearning{
    private:
        Enviroment env;
        agentAI agentPlayer;
        float alpha; //learning rate
        float gamma; //discount factor
        float epsilon; //exploration rate
        int episodes; //episodes of the agent
        // 3 dimension vector, where first vector is x, two vector is y,
        // Three vector is 4 vector probability move
        std::vector<std::vector<std::vector<float>>> qTable;
    public:
        qlearning(Enviroment envQlearn, agentAI agentQlearn): env(){
            env = envQlearn;
            agentPlayer = agentQlearn; 
            alpha = 0.5;
            gamma = 0.95;
            epsilon = 0.1;
            episodes = 10;
            //qTable.push_back({ { 1.3, 2.6, 3.1, 4.4 }, { 3.7, 2.8, 1.3, 2.4 } });
            //qTable.push_back({ { 1.2, 2.4, 3.2, 4.5 }, { 1.6, 2.8, 3.2, 4.4 } });
            
            //std::cout << "Max number: " << FindMaxQtable() << std::endl; 
        }
        float FindMaxQtable(){
            std::vector<float> flatQtable;
            for (int x = 0; x < qTable.size(); x++) {
                for (int y = 0; y < qTable[x].size(); y++) {
                    for (int q = 0; q < qTable[x][y].size(); q++) {
                        flatQtable.push_back(qTable[x][y][q]);
                    }
                }
            }
            return *max_element(flatQtable.begin(), flatQtable.end());;
        }
        float FindMax(std::vector<float> table){
            return *max_element(table.begin(), table.end());
        }
        void PrintQtable(){
            // Printing the 3d vector
            for (int x = 0; x < qTable.size(); x++) {
                for (int y = 0; y < qTable[x].size(); y++) {
                    for (int q = 0; q < qTable[x][y].size(); q++) {
                        std::cout << qTable[x][y][q] << " ";
                    }
                std::cout << std::endl;
                }
            }
        }
        float ChooseAction(int xpos, int ypos){
            if (randomFloat() < epsilon){
                return (float)agentPlayer.GetRandomDirectionMove(env); 
            }else{
                return FindMax(qTable[xpos][ypos]);
            }
        }
        void UpdateQtable(int xqtable, int yqtable, int action, float reward, int xnew, int ynew){
            qTable[xqtable][yqtable][action] = (1.0 - alpha) * qTable[xqtable][yqtable][action] + alpha * (reward + gamma * FindMax(qTable[xnew][ynew])); 
        }
        void Train(){
        }
};
