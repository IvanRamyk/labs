#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <cstdio>

const int CNT_FILES = 3;
const int MAX_CNT_IN_CHUNK = 10;

std::vector<std::vector <int>> files;
std::vector<int> source;
std::vector<std::ifstream> input_files;
std::vector<std::ofstream> output_files;

void quick_sort(std::vector <int> &numbers, int l = 0, int r = -1){
    if (r == -1)
        r = numbers.size() - 1;
    if (l >= r) return;
    int m = (l + r) >> 1;
    int i = l, j = r;
    while (i <= j){
        while (numbers[i] < numbers[m]) ++i;
        while (numbers[j] > numbers[m]) --j;
        if (i < j)
            std::swap(numbers[i], numbers[j]);
        else
            break;
        i++;
        j--;
    }
    quick_sort(numbers, l, j);
    quick_sort(numbers, j + 1, r);
}

std::vector<int> cnt_chunks_in_file(int minimal_cnt_chunks){
    std::vector <int> dp_chunks;
    dp_chunks.resize(CNT_FILES, 0);
    dp_chunks[0] = 1;
    int total = 1;
    while (total <= minimal_cnt_chunks) {
        int index_max = 0;
        for (int i = 0; i < CNT_FILES; ++i)
            if (dp_chunks[i] > dp_chunks[index_max])
                index_max = i;
        int Max = dp_chunks[index_max];
        for (int i = 0; i < CNT_FILES; ++i)
            if (i == index_max)
                dp_chunks[i] = 0;
            else {
                dp_chunks[i] += Max;
            }
        total += Max * (CNT_FILES - 2);
    }
    return dp_chunks;
}

int minimal_cnt_in_chunks(int file_size){
    return file_size / MAX_CNT_IN_CHUNK;
}

void sort_chunk(std::vector<int> &chunk){
    sort(chunk.begin(), chunk.end());
}

int cnt_increment_chunks(int file_size, int cnt_chunks){
    return file_size % cnt_chunks;
}

int minimal_cnt_of_chunks(int file_size){
    return (file_size + MAX_CNT_IN_CHUNK - 1) / MAX_CNT_IN_CHUNK;
}

void test_sort(){
    int n;
    std::cin >> n;
    std::vector <int> vec;
    vec.resize(n);
    for (int i = 0; i < n; ++i)
        std::cin >> vec[i];
    quick_sort(vec);
    for (int i = 0; i < n; ++i)
        std::cout << vec[i] << " ";
    std::cout << "\n";
}

void test_chunks(){
    int n;
    std::cin >> n;
    std::vector <int> answer = cnt_chunks_in_file(n);
    for (int i = 0; i < CNT_FILES; ++i)
        std::cout << answer[i] << " ";
}

int get_int_from_file(int file_number){
    int answer;
    input_files[file_number].read((char *)& answer, sizeof(answer));
    return answer;
}

int get_int_from_source(std::ifstream &input){
    int answer;
    input.read((char *)&answer, sizeof(answer));
    return answer;
}

void push_int_to_file(int file_number, int value){
    output_files[file_number].write((char *)&value, sizeof(value));
}

void chunk_to_file(std::vector <int> chunk, int file_number){
    for (auto i : chunk) {
        output_files[file_number].write((char *) &i, sizeof(i));
    }
    int cur = -1;
    output_files[file_number].write((char *)&cur, sizeof(cur));
}


std::vector<int> get_chunk(int chunk_size, std::ifstream &input){
    std::vector<int> chunk;
    chunk.resize(chunk_size);
    for (int i = 0; i < chunk_size; ++i){
        chunk[i] = get_int_from_source(input);
    }
    return chunk;
}

void print_chunk(std::vector <int> chunk){
    for (auto i : chunk)
        std::cout << i << " ";
    std::cout << "\n";
}

std::vector<int> set_chunks(){
    std::string file_mask = "file";
    for (int i = 0; i < CNT_FILES; ++i)
        output_files[i].open(std::to_string(i) + file_mask, std::ios::binary);
    std::ifstream input("Sources", std::ios::binary);
    int file_size = get_int_from_source(input);
    std::cout << file_size << "\n";
    int minimal_count_of_chunks = minimal_cnt_of_chunks(file_size);
    std::vector <int> cnt_in_file = cnt_chunks_in_file(minimal_count_of_chunks);
    int cnt_chunks = 0;
    for (int i = 0; i < cnt_in_file.size(); ++i)
        cnt_chunks += cnt_in_file[i];
    int cnt_in_chunk = file_size / cnt_chunks;
    int cnt_in_increment_chunk = cnt_in_chunk + 1;
    int cnt_increment = cnt_increment_chunks(file_size, cnt_chunks);
    int cnt = 0;
    for (int i = 0; i < cnt_in_file.size(); ++i)
        for (int j = 0; j < cnt_in_file[i]; ++j){
            if (cnt_increment != 0){
                cnt_increment--;
                std::vector <int> chunk = get_chunk(cnt_in_increment_chunk, input);
                sort_chunk(chunk);
                chunk_to_file(chunk, i);
            }
            else {
                std::vector <int> chunk = get_chunk(cnt_in_chunk, input);
                sort_chunk(chunk);
                chunk_to_file(chunk, i);
            }
        }
    for (int i = 0; i < CNT_FILES; ++i)
        output_files[i].close();
    return cnt_in_file;
}

void merge_chunk(int destination){
    std::vector <int> queue;
    queue.resize(CNT_FILES);
    for (int i = 0; i < CNT_FILES; ++i)
        if (i != destination){
            queue[i] = get_int_from_file(i);
        }
    int pos = 0;
    while (pos != -1){
        pos = -1;
        for (int i = 0; i < CNT_FILES; ++i) {
            if (i == destination) continue;
            if (queue[i] == -1) {
                continue;
            }
            if ((pos == -1) || (queue[pos] > queue[i]))
                pos = i;
        }
        if (pos != -1) {
            push_int_to_file(destination, queue[pos]);
            queue[pos] = get_int_from_file(pos);
        }
    }
    push_int_to_file(destination, -1);
}

void merging(std::vector <int> cnt_in_files){
    bool sorted = false;
    while (!sorted) {
        int zero = -1;
        int minimal_cnt_chunks = 1e9;
        for (int i = 0; i < cnt_in_files.size(); ++i) {
            if (!cnt_in_files[i])  {
                if (zero != -1) {
                    sorted = true;
                    break;
                }
                else zero = i;
            }
            else if (cnt_in_files[i] < minimal_cnt_chunks)
                minimal_cnt_chunks = cnt_in_files[i];
        }
        if (!sorted) {
            input_files[zero].close();
            output_files[zero].open(std::to_string(zero) + "file", std::fstream::binary);
            for (int i = 0; i < minimal_cnt_chunks; ++i)
                merge_chunk(zero);
            output_files[zero].close();
            input_files[zero].open(std::to_string(zero) + "file", std::fstream::binary);
            for (int i = 0; i < cnt_in_files.size(); ++i)
                if (i == zero)
                    cnt_in_files[i] = minimal_cnt_chunks;
                else
                    cnt_in_files[i] -= minimal_cnt_chunks;
        }
    }
}


void set_files()
{
    std::string file_mask = "file";
    for (int i = 0; i < CNT_FILES; ++i)
        input_files[i].open(std::to_string(i) + file_mask, std::ios::binary);
}

void print_answer(){
    int answer = 0;
    while (answer >= 0){
        input_files[0].read((char *)&answer, sizeof(answer));
        std::cout << answer << " ";
    }
    std::cout << "\n";
}

void generate_source(){
    std::string file_name = "Sources";
    std::ofstream output(file_name,std::ios::binary);
    int n = 100000, k;
    std::vector <int> vec;
    vec.resize(n);
    output.write((char *)&n, sizeof(n));
    for (int i = 0; i < n; ++i){
        vec[i] = rand() % 1000;
        output.write((char*)&vec[i], sizeof(vec[i]));
    }
    output.close();
}

void print_files(){
    for (int i = 0; i < CNT_FILES; ++i){
        std::cout << i << " ";
        for (int j = 0; j < files[i].size(); ++j)
            std::cout << files[i][j] << " ";
        std::cout << "\n";
    }
}

int main() {
    srand(time(0));
    files.resize(CNT_FILES);
    input_files.resize(CNT_FILES);
    output_files.resize(CNT_FILES);
    generate_source();
    std::vector <int> chunks_in_files = set_chunks();
    set_files();
    merging(chunks_in_files);
    print_answer();
    return 0;
}
