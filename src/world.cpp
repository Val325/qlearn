class Enviroment{
    private:
        SDL_Window* win;
        SDL_Renderer* ren;
        std::vector<ImageCell> Cells;
        int sizeCells;
        int sizeCell;
    public:
        Enviroment(SDL_Window* window, SDL_Renderer* render, int sizeAllCells){
            win = window;
            ren = render;
            sizeCells = sizeAllCells;
            
            ImageCell cellOpen(win, ren);
            cellOpen.loadTexture("resource/images/cellopen.bmp");
            cellOpen.setSize(sizeCell, sizeCell);
            cellOpen.setWindow(win);
            cellOpen.setRender(ren);
            
            Cells.resize(sizeCells);
            for (int i = 0; i <= sizeCells; i++){
                Cells.push_back(cellOpen);
            }
        }
        void SetCellSize(int size){
            sizeCell = size;
        }
        void GenerateCells(int xsize, int ysize){
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> ran(0,3);
            
            int x = 0;
            int y = 0;
            for (int i = 0; i < sizeCells; i++){
                Cells[i].setPosition(x * sizeCell,y * sizeCell);
                Cells[i].setWindow(win);
                Cells[i].setRender(ren);
                Cells[i].setPositionGrid(x, y);
                Cells[i].setSize(sizeCell, sizeCell);
                (ran(rng) == 0) ? Cells[i].loadTexture("resource/images/cellobstacle.bmp"): Cells[i].loadTexture("resource/images/cellopen.bmp"); 
                x++;
                // x = 8
                if (x == xsize){
                    x = 0;
                    y++;
                }
                // y == 6
                if (y == ysize){
                    y = 0;
                }
                //std::cout << "random: " << ran(rng) << std::endl;
            }
        }
        void Render(){
            for (int i = 0; i < sizeCells; i++){
                Cells[i].render();
            }
        }
};
