struct Reward{
    int x;
    int y;
    float reward;
    bool done;
};

//random float in range 0.0..1.0
float randomFloat(){
    return (float)rand()/RAND_MAX;
}

template <typename T, typename A>
int arg_max(std::vector<T, A> const& vec) {
  return static_cast<int>(std::distance(vec.begin(), max_element(vec.begin(), vec.end())));
}

template <typename T, typename A>
int arg_min(std::vector<T, A> const& vec) {
  return static_cast<int>(std::distance(vec.begin(), min_element(vec.begin(), vec.end())));
}

struct State{
    int x;
    int y;
};
