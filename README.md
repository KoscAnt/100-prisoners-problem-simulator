# 100-prisoners-problem-simulator

A C++ implementation of the classic 100 Prisoners Problem, demonstrating the counterintuitive ~31% success probability achievable through optimal strategy.

## Mathematical Background
This C++ program simulates the **100 Prisoners Problem**, a classic probability puzzle that demonstrates a surprising statistical phenomenon:

- **100 prisoners** must individually find their number in **100 boxes**
- Each box contains a **random permutation** of numbers 1-100
- Prisoners may open **up to 50 boxes** (N/2 attempts)
- **All prisoners succeed** only if every one finds their number within the limit

- The optimal **follow-the-cycle strategy** yields a success probability of ~31%, vastly higher than random guessing (which would be (1/2)^100 ≈ 8×10⁻³¹%).

## How It Works
The simulation implements the mathematically proven optimal strategy:
1. Each prisoner starts by opening the box labeled with their own number
2. They follow the chain: next box = number found in current box
3. The process succeeds if all cycles are ≤50 in length

### Key Features
- Interactive menu system with 3 operation modes
- Customizable simulations (4 to 100 prisoners)
- Detailed chain visualization in output files
- Statistical analysis 10,000 trials

## Operation Modes
  ### Custom Simulation Mode
  - Lets users test smaller prisoner counts (4, 9, 16, 36, 64, or 100)
  - Each prisoner gets N/2 attempts (e.g., 2 tries for 4 prisoners)
  - Interactive experience: Users manually select boxes to:
    
      - Understand the problem mechanics
      - Test alternative strategies
      - Observe chain reactions visually
     
   
   ### Simulation Mode
   - Runs the standard 100-prisoner scenario
   - User selects: Number of trials (1-100)
   - Output:
     
      - For 1 trial: Full chain details for each prisoner
      - For 2-100 trials: Success rate percentage

  ### Statistical Mode
  - Automatically runs 10,000 simulations
  - Purpose: Verifies the theoretical ~31% success rate
  - Writes batch results to statistics.txt

## Program Structure

- `number_boxes()`: Initializes a 10×10 matrix with sequential numbers 1-100  
- `matrix_generate()`: Shuffles numbers 1-100 into random permutations using Mersenne Twister  
- `matrix_print()`: Displays the current state of the matrix (debugging tool)  
- `find_first_number()`: Locates a prisoner's starting box number in the matrix  
- `sent_prisoners()`: Runs the main simulation with detailed logging to results.txt  
- `sent_prisoners_for_stats()`: Runs the prisoner simulation without logging and returns 1 (success) if all prisoners find their number within 50 attempts, 0 (failure) otherwise
- `stats()`: Performs 100 simulation runs to calculate success rate  
- `stats_hundrets_times()`: Executes 10,000 total simulations (100 batches of 100)  
- `customSimulation4/9/16/36/64/100()`: Interactive simulations for N prisoners (N=4 to 100) with user-input box selection 

