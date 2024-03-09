

class agentAI{
    private:
        int moveSizeCell;
        //grid
        int x;
        int y;
        
        //constraint cells
        int xSizeCells;
        int ySizeCells;

        SDL_Window* win;
        SDL_Renderer* ren;

        SDL_Surface* agentSurface;
        SDL_Texture* textureAgent;
        //coordinate image
        SDL_Rect AgentRect;

        std::string pathTexture;
        
        bool isGoalEnd;
        int xGoal;
        int yGoal;
        void loadSurface(std::string pathSurf){
            agentSurface = SDL_LoadBMP(pathSurf.c_str());

	        if (agentSurface == NULL) {
		        fprintf(stderr, "SDL_LoadBMP Error: %s\n", SDL_GetError());
		        SDL_DestroyRenderer(ren);
		        SDL_DestroyWindow(win);
		        SDL_Quit();
	        }
        }
    public:
        agentAI(){
            moveSizeCell = 100;
            x = 0;
            y = 0;
        }
        agentAI(int xpos, int ypos){
            moveSizeCell = 100;
            x = xpos;
            y = ypos;
        }
        void setWindow(SDL_Window* window){
            win = window;
        }
        void setRender(SDL_Renderer* render){
            ren = render;
        }
        void loadTexture(std::string pathTex){
            loadSurface(pathTex); 
            textureAgent = SDL_CreateTextureFromSurface(ren, agentSurface);
	        
            if (textureAgent == NULL) {
		        fprintf(stderr, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
		        SDL_FreeSurface(agentSurface);
		        SDL_DestroyRenderer(ren);
		        SDL_DestroyWindow(win);
		        SDL_Quit();
	        }
        }
        int getXposition(){
            return x;
        }
        int getYposition(){
            return y;
        }
        void setGoal(int xpos, int ypos){
            xGoal = xpos;
            yGoal = ypos;
        }
        void GetGoal(){
            isGoalEnd = true;
        }
        bool isGetGoal(){
            return isGoalEnd; 
        }
        void setConstraint(int xconstr, int yconstr){
            xSizeCells = xconstr;
            ySizeCells = yconstr;
        }
        void setPosition(int x, int y){
            AgentRect.x = x;
            AgentRect.y = y;
        }
        SDL_Rect getPosition(){
            return AgentRect; 
        }
        void setSize(int width, int height){
            AgentRect.w = width;
            AgentRect.h = height;
        }
        void MoveUp(){
            int yTopPos = 0;
            if (y > yTopPos){
                y--;
                AgentRect.y = y * moveSizeCell;
            }
        }
        void MoveDown(){
            int yTopPos = 0;
            int offsetY = 1;
            if (y < ySizeCells - offsetY){
                y++;
                AgentRect.y = y * moveSizeCell;
            }
        }
        void MoveRight(){
            int xTopPos = 0;
            if (x <= ySizeCells){
                x++;
                AgentRect.x = x * moveSizeCell;
            }
        }
        void MoveLeft(){
            int xTopPos = 0;
            if (x > xTopPos){
                x--;
                AgentRect.x = x * moveSizeCell;
            }
        }
        void DontMove(){
            AgentRect.x = AgentRect.x;
            AgentRect.y = AgentRect.y;
        }
        void MovePlayer(int act){
            if (act == 0) MoveUp();
            if (act == 1) MoveDown();
            if (act == 2) MoveRight();
            if (act == 3) MoveLeft();
            if (act == 4) DontMove();
        }
        void RandomDirectionMove(Enviroment universe){
            ImageCell cellNearbyPlayer;
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> ran(0,3);
            Reward DataReward;
            /////////////////////////////////////////////////////////////////////////////////////////////// 
            // Up
            ///////////////////////////////////////////////////////////////////////////////////////////////
            if ((getYposition() - 1) >= 0){
                cellNearbyPlayer = universe.getCellPosition(getXposition(), getYposition() - 1);
            }
            if (!cellNearbyPlayer.getCollide()){ 
                if (ran(rng) == 0) MoveUp();
                
            }
            /////////////////////////////////////////////////////////////////////////////////////////////// 
            // Down
            ///////////////////////////////////////////////////////////////////////////////////////////////
            if ((getYposition() + 1) < ySizeCells){
                cellNearbyPlayer = universe.getCellPosition(getXposition(), getYposition() + 1);
            }
            if (!cellNearbyPlayer.getCollide()){                                
                if (ran(rng) == 1) MoveDown();
            }
            /////////////////////////////////////////////////////////////////////////////////////////////// 
            // Right
            ///////////////////////////////////////////////////////////////////////////////////////////////
            if ((getXposition() + 1) < xSizeCells){ 
                cellNearbyPlayer = universe.getCellPosition(getXposition() + 1, getYposition());
            }
            if (!cellNearbyPlayer.getCollide()){
                if (ran(rng) == 2) MoveRight();
            }
            /////////////////////////////////////////////////////////////////////////////////////////////// 
            // Left
            ///////////////////////////////////////////////////////////////////////////////////////////////
            if ((getXposition() - 1) == -1){
                cellNearbyPlayer = universe.getCellPosition(getXposition(), getYposition());
            }else{
                cellNearbyPlayer = universe.getCellPosition(getXposition() - 1, getYposition());
            }
            if (!cellNearbyPlayer.getCollide()){
                if (ran(rng) == 3) MoveLeft();
            }
        }
        int GetRandomDirectionMove(Enviroment universe){
            ImageCell cellNearbyPlayer;
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> ran(0,3);
            /////////////////////////////////////////////////////////////////////////////////////////////// 
            // Up
            ///////////////////////////////////////////////////////////////////////////////////////////////
            if ((getYposition() - 1) >= 0){
                cellNearbyPlayer = universe.getCellPosition(getXposition(), getYposition() - 1);
            }
            if (!cellNearbyPlayer.getCollide()){ 
                if (ran(rng) == 0){
                    MoveUp();
                    return 0; 
                }
            }
            /////////////////////////////////////////////////////////////////////////////////////////////// 
            // Down
            ///////////////////////////////////////////////////////////////////////////////////////////////
            if ((getYposition() + 1) < ySizeCells){
                cellNearbyPlayer = universe.getCellPosition(getXposition(), getYposition() + 1);
            }
            if (!cellNearbyPlayer.getCollide()){                                
                if (ran(rng) == 1){              
                    MoveDown();
                    return 1; 
                }
            }
            /////////////////////////////////////////////////////////////////////////////////////////////// 
            // Right
            ///////////////////////////////////////////////////////////////////////////////////////////////
            if ((getXposition() + 1) < xSizeCells){ 
                cellNearbyPlayer = universe.getCellPosition(getXposition() + 1, getYposition());
            }
            if (!cellNearbyPlayer.getCollide()){
                if (ran(rng) == 2){
                    MoveRight();
                    return 2; 
                }
            }
            /////////////////////////////////////////////////////////////////////////////////////////////// 
            // Left
            ///////////////////////////////////////////////////////////////////////////////////////////////
            if ((getXposition() - 1) == -1){
                cellNearbyPlayer = universe.getCellPosition(getXposition(), getYposition());
            }else{
                cellNearbyPlayer = universe.getCellPosition(getXposition() - 1, getYposition());
            }
            if (!cellNearbyPlayer.getCollide()){
                if (ran(rng) == 3){
                    MoveLeft();
                    return 3; 
                }
            }
            return 4;
        }
        Reward GetRewardRandomDirectionMove(Enviroment universe){
            ImageCell cellNearbyPlayer;
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> ran(0,3);
            Reward rewardData;
            /////////////////////////////////////////////////////////////////////////////////////////////// 
            // Up
            ///////////////////////////////////////////////////////////////////////////////////////////////
            if ((getYposition() - 1) >= 0){
                cellNearbyPlayer = universe.getCellPosition(getXposition(), getYposition() - 1);
            }
            if (!cellNearbyPlayer.getCollide()){ 
                if (ran(rng) == 0){
                    MoveUp();
                    rewardData.x = getXposition();
                    rewardData.y = getYposition() - 1;
                    if (getYposition() - 1 == -1) rewardData.y = getYposition();
                    rewardData.reward = -0.01;
                    rewardData.action = 0;
                    rewardData.done = false;

                    return rewardData; 
                }
            }
            /////////////////////////////////////////////////////////////////////////////////////////////// 
            // Down
            ///////////////////////////////////////////////////////////////////////////////////////////////
            if ((getYposition() + 1) < ySizeCells){
                cellNearbyPlayer = universe.getCellPosition(getXposition(), getYposition() + 1);
            }
            if (!cellNearbyPlayer.getCollide()){                                
                if (ran(rng) == 1){              
                    MoveDown();
                    rewardData.x = getXposition();
                    rewardData.y = getYposition() + 1;
                    rewardData.reward = -0.01;
                    rewardData.action = 1;
                    rewardData.done = false;

                    return rewardData; 
                }
            }
            /////////////////////////////////////////////////////////////////////////////////////////////// 
            // Right
            ///////////////////////////////////////////////////////////////////////////////////////////////
            if ((getXposition() + 1) < xSizeCells){ 
                cellNearbyPlayer = universe.getCellPosition(getXposition() + 1, getYposition());
            }
            if (!cellNearbyPlayer.getCollide()){
                if (ran(rng) == 2){
                    MoveRight();
                    rewardData.x = getXposition() + 1;
                    rewardData.y = getYposition();
                    rewardData.reward = -0.01;
                    rewardData.action = 2;
                    rewardData.done = false;

                    return rewardData; 
                }
            }
            /////////////////////////////////////////////////////////////////////////////////////////////// 
            // Left
            ///////////////////////////////////////////////////////////////////////////////////////////////
            if ((getXposition() - 1) == -1){
                cellNearbyPlayer = universe.getCellPosition(getXposition(), getYposition());
            }else{
                cellNearbyPlayer = universe.getCellPosition(getXposition() - 1, getYposition());
            }
            if (!cellNearbyPlayer.getCollide()){
                if (ran(rng) == 3){
                    MoveLeft();
                    rewardData.x = getXposition() - 1;
                    if (getXposition() - 1 == -1) rewardData.x = getXposition(); 
                    rewardData.y = getYposition();
                    rewardData.action = 3;
                    rewardData.reward = -0.01;
                    rewardData.done = false;

                    return rewardData; 
                }
            }

            //std::cout << "x :" << rewardData.x << std::endl;
            //std::cout << "y :" << rewardData.y << std::endl;
            //std::cout << "reward :" << rewardData.reward << std::endl;

            rewardData.x = getXposition();
            rewardData.y = getYposition();
            rewardData.reward = -0.01;
            rewardData.action = 4;
            rewardData.done = false;
            return rewardData; 
        }
        State Reset(){
            State startPosition;
            startPosition.x = 0;
            startPosition.y = 0;
            setPosition(0, 0);
            return startPosition; 
        }
        void Render(){
            if (ren == NULL) std::cout << "ren agent null" << std::endl;
            if (textureAgent == NULL) std::cout << "tex agent null" << std::endl;
            //std::cout << "x: " << x << "y: " << y << "w: " << x << "h: " << std::endl;
            SDL_RenderCopy(ren, textureAgent, NULL, &AgentRect);
        }
        bool checkCollision(SDL_Rect player_rect){
            //The sides of the rectangles
            int leftA, leftB;
            int rightA, rightB;
            int topA, topB;
            int bottomA, bottomB;

            //Calculate the sides of rect A
            leftA = player_rect.x;
            rightA = player_rect.x + player_rect.w;
            topA = player_rect.y;
            bottomA = player_rect.y + player_rect.h;

            //Calculate the sides of rect B
            leftB = AgentRect.x;
            rightB = AgentRect.x + AgentRect.w;
            topB = AgentRect.y;
            bottomB = AgentRect.y + AgentRect.h;
            
            //If any of the sides from A are outside of B
            if( bottomA <= topB ){
                return false;
            }

            if( topA >= bottomB ){
                return false;
            }

            if( rightA <= leftB ){
                return false;
            }

            if( leftA >= rightB ){
                return false;
            }

            //If none of the sides from A are outside B
            return true;
        }
};
