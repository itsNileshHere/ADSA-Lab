## Problem
You are a quality-control engineer in a coin-making company. Among n coins, one coin might be lighter (defective) while the rest are identical in weight, or all could be perfect. Using a balance scale, design a divide and conquer algorithm to identify the lighter coin (if it exists) or report none, with time complexity O(log₂n + c).


## Key Requirements
1. Find the **lighter coin** (if it exists).  
2. If all coins are identical in weight, report **no defective coin**.  
3. Use **divide and conquer** with a **balance scale**.  


## Divide and Conquer
We can reduce comparisons by repeatedly dividing the pile:

1. **Split coins into two halves**.  
2. **Weigh the two halves** using the balance scale.  
   - If one half is lighter → defective coin is inside that half.  
   - If both halves are equal → either the defective coin is in the other section or no defective coin exists.  
3. **Recursively search** until only one coin is left.  

This reduces the problem size by half at each step.


## Approach
This C Program

- Divide the coins into two equal groups. 
- Use the balance scale to compare the left half with the right half.  
- Check the result of weighing
    - **Left lighter →** defective coin must be in the left half.  
    - **Right lighter →** defective coin must be in the right half.  
    - **Equal →** either no defective coin exists or the coin outside the comparison set is perfect.  
- Recurse until only one coin remains.
- If that coin is strictly lighter than a reference coin, report it as defective.  
- Otherwise, conclude **no defective coin exists**.  


## Complexity Analysis
- **Time Complexity:** `O(log n)` weighings due to halving at each step.  
- **Space Complexity:** `O(log n)` recursion stack (or `O(1)` with iterative approach).  
- **Accuracy:** Always detects a lighter coin if present; otherwise safely reports none.  