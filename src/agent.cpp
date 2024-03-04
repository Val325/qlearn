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
        void Render(){
            if (ren == NULL) std::cout << "ren agent null" << std::endl;
            if (textureAgent == NULL) std::cout << "tex agent null" << std::endl;
            //std::cout << "x: " << x << "y: " << y << "w: " << x << "h: " << std::endl;
            SDL_RenderCopy(ren, textureAgent, NULL, &AgentRect);
        }
};
