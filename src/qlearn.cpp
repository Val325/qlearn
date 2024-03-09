

class qlearning{
    private:
        Enviroment *env;
        agentAI *agentPlayer;
        int xSizeCells;
        int ySizeCells;
        bool quit = false;
        bool isStartGame = false;
        bool isGame = false;
        bool isStartQlearning = false;
        float alpha; //learning rate
        float gamma; //discount factor
        float epsilon; //exploration rate
        int episodes; //episodes of the agent
        // 3 dimension vector, where first vector is x, two vector is y,
        // Three vector is 4 vector probability move
        std::vector<std::vector<std::vector<float>>> qTable;
        Reward rewardAgent;
        State startpos;
        SDL_Event e;
    public:
        qlearning(Enviroment *envQlearn, agentAI *agentQlearn, int xSize, int ySize): env(){

            env = envQlearn;
            agentPlayer = agentQlearn; 
            xSizeCells = xSize; 
            ySizeCells = ySize;
            alpha = 0.5;
            gamma = 0.95;
            epsilon = 0.5;
            episodes = 10;
            //qTable.push_back({ { 1.3, 2.6, 3.1, 4.4 }, { 3.7, 2.8, 1.3, 2.4 } });
            //qTable.push_back({ { 1.2, 2.4, 3.2, 4.5 }, { 1.6, 2.8, 3.2, 4.4 } });
            startpos = agentPlayer->Reset(); 
            quit = false;
            isStartGame = false;
            isGame = false;
            isStartQlearning = false; 
            qTable.resize(xSize);
            //std::cout << "Xsize: " <<  xSize << std::endl;
            //std::cout << "Ysize: " <<  ySize << std::endl; 
            for (int i = 0; i < qTable.size(); i++){
                qTable[i].resize(ySize );
                for (int j = 0; j < qTable[i].size(); j++){
                    qTable[i][j].resize(5);
                }
            }
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
            //std::cout << "Find max: " << *max_element(qTable[x][y].begin(), qTable[x][y].end()) << std::endl; 
            //std::cout << "X: " << x << std::endl;
            //std::cout << "Y: " << y << std::endl;
            //std::cout << "Table size: " << table.size() << std::endl;
            //std::cout << "Max elem: " << *max_element(table.begin(), table.end()) << std::endl;

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
        int ChooseAction(int xpos, int ypos){
            if (randomFloat() < epsilon){
                int direction = agentPlayer->GetRandomDirectionMove(*env);
                //std::cout << "randomDirection epsilon " << direction << std::endl; 
                return direction; 
            }else{
                int argMax = arg_max(qTable[xpos][ypos]);
                //std::cout << "arg max " << argMax << std::endl; 
                return argMax;            
            }
        }
        void UpdateQtable(int xqtable, int yqtable, int action, float reward, int xnew, int ynew){
            //std::cout << "qtable new: " << qTable[xnew][ynew] << std::endl;
            /*
            std::cout << "-- DATA --" << std::endl;
            std::cout << "xqtable: " << xqtable << std::endl;
            std::cout << "yqtable: " << yqtable << std::endl;
            std::cout << "action: " << action << std::endl;
            std::cout << "reward: " << reward << std::endl;
            std::cout << "xnew: " << xnew << std::endl;
            std::cout << "ynew: " << ynew << std::endl;
             
            std::cout << "-- DEBUG SIZE ARRAYS --" << std::endl;
            std::cout << "xqtable: " << xqtable << std::endl;
            std::cout << "xqtable size: " << qTable.size() << std::endl;
            std::cout << "yqtable : " << yqtable << std::endl;
            */
            //std::cout << "yqtable size: " << qTable[xqtable].size() << std::endl;
            //std::cout << "Find max: " << FindMax(qTable[xqtable][yqtable]) << std::endl;
            std::cout << "action: " << action << std::endl;
            //std::cout << "action size: " << qTable[xqtable][yqtable].size() << std::endl;
            //std::cout << "qtable action: " << qTable[xqtable][yqtable][action] << std::endl;
            
            if (yqtable == 6){
                qTable[xqtable][yqtable - 1][action] = (1.0 - alpha) * qTable[xqtable][yqtable - 1][action] + alpha * (reward + gamma * FindMax(qTable[xqtable][yqtable - 1]));

                //std::cout << "qtable: " << qTable[xqtable][yqtable - 1][action] << std::endl; 
            } else if (xqtable == 8){
                qTable[xqtable - 1][yqtable][action] = (1.0 - alpha) * qTable[xqtable - 1][yqtable][action] + alpha * (reward + gamma * FindMax(qTable[xqtable -1][yqtable]));
                //std::cout << "qtable: " << qTable[xqtable - 1][yqtable][action] << std::endl; 

            }else{
                qTable[xqtable][yqtable][action] = (1.0 - alpha) * qTable[xqtable][yqtable][action] + alpha * (reward + gamma * FindMax(qTable[xqtable][yqtable]));

                //std::cout << "qtable: " << qTable[xqtable][yqtable][action] << std::endl; 
            }



        }
        void MovePlayer(int act){
            /////////////////////////////////////////////////////////////////////////////////////////////// 
            // Up
            ///////////////////////////////////////////////////////////////////////////////////////////////
            if (act == 0) agentPlayer->MoveUp();
            /////////////////////////////////////////////////////////////////////////////////////////////// 
            // Down
            ///////////////////////////////////////////////////////////////////////////////////////////////
            if (act == 1) agentPlayer->MoveDown();
            /////////////////////////////////////////////////////////////////////////////////////////////// 
            // Right
            ///////////////////////////////////////////////////////////////////////////////////////////////
            if (act == 2) agentPlayer->MoveRight();
            /////////////////////////////////////////////////////////////////////////////////////////////// 
            // Left
            ///////////////////////////////////////////////////////////////////////////////////////////////
            if (act == 3) agentPlayer->MoveLeft();

        }

        void Init(){
            //std::thread t1(&qlearning::Render, this);
            //std::thread t2(&qlearning::Train, this);
            //std::thread t3(&qlearning::sdlEvents, this);         
            //t1.join();
            //t2.join();
            //t3.join();
            //Train();
            //Render();
        }
        void Render(){
            env->Render();
            //endpoint.Render();
            //agentPlayer->setPosition(rewardAgent.x, rewardAgent.y);
            agentPlayer->Render();
            
        }
        int getAction(){
            return rewardAgent.action; 
        }

        void Train(){
            std::vector<float> rewards;
            std::vector<State> states;
            std::vector<State> starts;
            std::vector<State> stepsPerEpisode;
            
            int steps = 0;
            int episode = 0;
            float totalReward = 0.0;
            bool isDone = false; 
                    int act = ChooseAction(startpos.x, startpos.y);

                    rewardAgent = agentPlayer->GetRewardRandomDirectionMove(*env);

                    //std::cout << "action: " << getAction() << std::endl; 
                    //MovePlayer(rewardAgent.action); 
                    //agentPlayer->MovePlayer();
                    UpdateQtable(startpos.x, startpos.y, act, rewardAgent.reward, rewardAgent.x, rewardAgent.y); 
                    

                    isDone = rewardAgent.done;
                    startpos.x = rewardAgent.x;
                    startpos.y = rewardAgent.y;

                    totalReward += rewardAgent.reward;

                    states.push_back(startpos);
                    steps++;
                    //Render();
                    if (isDone && agentPlayer->isGetGoal()){
                        steps = 0;
                        episode++;
                    }
            /*
            while (episode < episodes){
                

                while (!isDone){

                }
            }*/
        }
};
