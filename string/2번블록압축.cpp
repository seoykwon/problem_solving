/*
이중 벡터로 mapdata 주어지고 n이라는 압축률이 주어짐
변의 길이를 압축해야 함.
n이 3이고 mapdata의 한 변의 길이가 3이면 변의 길이가 1인 블록으로 압축해서 그 벡터를 리턴해야 함.
이때 압축할 때 제일 많이 등장하는 수가 그 블록을 대표하게 됨.
만약 많이 등장하는 횟수가 같다면 가장 큰 수가 그 블록을 대표함.
*/