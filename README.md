# AlgorithmLee
Wave algorithm that find the shortest path on map, from one point to another

# Input/Output examples

Input file:
<p>
<img src="https://github.com/experiencecool/AlgorithmLee/blob/master/input.png">
  </p>
 Output file:
 <p><img src="https://github.com/experiencecool/AlgorithmLee/blob/master/output.png"></p>
 <ul>Legend:
 <p>'0' = free spaces</p>
 <p>'1' = wall</p>
 <p>'2' = start point</p>
 <p>'3' = finish point</p>
 <p>'*' = path</p>
  </ul>
  
# Discription

<p>
  The Lee algorithm is one possible solution for maze routing problems based on Breadth-first search. It always gives an optimal solution, if one exists, but is slow and requires considerable memory. It called "Wave algorithm" becouse it behaves like an wave. It begins from the start point and on every next step it takes all neighbours points and recursively applies for each of them untill finish point was taken or there is no more points to take.
  </p>
