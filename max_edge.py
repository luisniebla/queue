

from array import *

def maximalNetworkRank(n, roads):
    edgeNetworkRanks = [[0 for x in range(n)] for y in range(n)] 
    for road in roads:
        edgeNetworkRanks[road[0]][road[1]] += 1
        edgeNetworkRanks[road[1]][road[0]] += 1
    
    maxRanks = {}
    for i in range(len(edgeNetworkRanks)):
        maxRanks[i] = sum(edgeNetworkRanks[i])
    maxValue = 0
    index1 = 0
    index2 = 0
    for k, v in maxRanks.items():
        for q, m in maxRanks.items():
            if k != q:
                if maxValue < v + m:
                    if [k, q] in roads or [q, k] in roads:
                        maxValue = v + m - 1
                    else:
                        maxValue = v + m
    return maxValue
    
    # rank1 = max(maxRanks.values())
    # index1 = 0
    # for k, v in maxRanks.items():
    #     # print('k, v', k, v)
    #     if v == rank1:
    #         # print('found rank', k, v)
    #         maxRanks[k] = 0
    #         index1 = k
    #         break
    # print('new ranks', maxRanks)
    # rank2 = max(maxRanks.values())
    # print('RANK2 FOUND...', rank2)
    # index2 = 0
    # for k, v in maxRanks.items():
    #     if v == rank2:
    #         print('FOUND INDEX FOR rank2', rank2, k, v)
    #         index2 = k
    #         break
    # print(f'{index1}: {rank1}; {index2}: {rank2}')
    # print('ROADS: ', roads)
    
    # return rank1 + rank2

print(maximalNetworkRank(4, [[0,1],[0,3],[1,2],[1,3]]))
print(maximalNetworkRank(5, [[0,1],[0,3],[1,2],[1,3],[2,3],[2,4]]))
print(maximalNetworkRank(8, [[0,1],[1,2],[2,3],[2,4],[5,6],[5,7]]))