
// +-----------------+ //
// | Include Headers | //
// +-----------------+ //

#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>

// +--------------------------+ //
// | Declare Global Variables | //
// +--------------------------+ //

std::vector<int> visited_perm; // initialise to pass into unary predicate

// +-----------------------------+ //
// | Declare Secondary Functions | //
// +-----------------------------+ //

bool PatternIsPresent(std::vector<int> init_vec, std::vector<int> substring){

    /*  Determines whether the relative ordering of a substring is identifiable
        in the input vector. Returns true if present, false otherwise. 

    */
                                             
    // Characterise Pattern indicated by substring

    std::function<int(int, int)> op_1 = std::less<int>();
    std::function<int(int, int)> op_2 = std::less<int>();
    std::function<int(int, int)> op_3 = std::less<int>();

    if (substring[0]>substring[1]){ // check ordering between zeroth and first indices
        op_1 = std::greater<int>();
        
    }
    if (substring[1]>substring[2]){ // check ordering between first and second indices
        op_2 = std::greater<int>();
        
    }
    if (substring[0]>substring[2]){ // check ordering between zeroth and second indices
        op_3 = std::greater<int>();
        
    }


    // Find whether this pattern is present in init_vec
    
    for(int i=0; i!=init_vec.size()-2;i++){ // the last two indices can't contain a length 3 substring
        
        int P_One = init_vec[i];
        
        for(int j=i+1; j!=init_vec.size()-1;j++){ // the last index can't contain a length 2 substring

            int P_Two = init_vec[j];

            if (op_1(P_One, P_Two)){
                
                for(int k= j+1; k!=init_vec.size();k++){ // search for the final corresponding index

                    int P_Three = init_vec[k];

                    if (op_2(P_Two,P_Three) && op_3(P_One,P_Three)){
                        
                        std::cout << P_One << P_Two << P_Three << "\n";
                        return true;
                    } 
                    

                }

            }
        }

    }

    return false;

}

void printp_vec(std::vector<std::vector<int>> container){

    /* Outputs permutations to the console by iterating through
       vector of vectors (vector of permutations).

       std::vector<std::vector<int>> 'container': 2D vector object with stored permutations
    */

    int perm_len = container[0].size();
    int num_of_perms = container.size();

    for(int i=0;i<num_of_perms;i++){
        std::vector<int> perm_i = container[i];
        for(int j=0;j<perm_len;j++){
            std::cout << perm_i[j];

        }
        std::cout << "\n";
    }
}

std::vector<int> order_id(std::vector<int> vec_uo){

    /*  Takes an input vector and sorts it by ascending (id_n) order. 

        std::vector<int> 'vec_uo': vector to be reordered
    
     */

    sort(vec_uo.begin(), vec_uo.end());
    return vec_uo;
}

// +---------------------------+ //
// | Declare Primary Functions | //
// +---------------------------+ //

std::vector<int> r_jump(std::vector<int> init_vec, int s_index, int steps){

    /*  Performs a cyclic left rotation of the substring a_i ... a_j
        to a_i+1 ... a_j a_i by one position to move a_i by j-i steps
        to the right.

        std::vector<int> 'init_vec': vector to be rotated
        int 's_index': element to perform jump (a_i)
        int 'steps': Size of jump (j-i)  

    */

    auto first = init_vec.begin()+s_index;; // Point to 1st element of substring (inclusive)
    auto last = first+steps+1; // Point to just after last element of substring 
    std::rotate(first, first+1, last);

    return init_vec;


}

std::vector<int> l_jump(std::vector<int> init_vec, int s_index, int steps){

    /*  Performs a cyclic right rotation of the substring a_i ... a_j
        to a_j a_i ... a_j-1 by one position to move a_j by j-i steps
        to the left.

        std::vector<int> 'init_vec': vector to be rotated
        int 's_index': element to perform jump (a_j)
        int 'steps': Size of jump (j-i)  

    */

    auto first = init_vec.rbegin()+(init_vec.size()-1-s_index);; // Point to 1st element of substring (inclusive)
    auto last = first+steps+1; // Point to just after last element of substring 
    std::rotate(first, first+1, last);

    return init_vec;

}

std::vector<int> min_jump(std::vector<int> pi_i,  std::vector<std::vector<int>> update_vec, std::vector<int> pattern ){

    /*  Attempts to perform a minimal jump on an input permutation given some pattern substring
        to avoid and an iterative list of visited permutations. If no jumps are possible/
        jump direction is ambiguous then terminate Algorithm J.

        std::vector<int> 'pi_i': A minimal jump will be performed on this permutation
        std::vector<std::vector<int>> 'update_vec': The list of visited permutations
        std::vector<int> 'pattern': The substring pattern to be avoided  

    */
     
    std::vector<int> ordered_vec = order_id(pi_i);

    for(int i=ordered_vec.size()-1;i>0;i--){
        std::cout << "For ith value: " << ordered_vec[i] <<  "\n";  

        int mov_val = ordered_vec[i];
        int mov_ind = std::find(pi_i.begin(),pi_i.end(),mov_val) - pi_i.begin();

        int r_max; // maximum right jump after considering rightward larger neighbours (if any)
        int l_max; // maximum left jump after considering leftward larger neighbours (if any)

        auto is_larger = [mov_val](int val){return val>mov_val;}; // predicate function to check for larger neighbours
        
        auto r_check = std::find_if(pi_i.begin()+mov_ind, pi_i.end(), is_larger); 
        auto l_check = std::find_if(pi_i.rbegin()+pi_i.size()-1-mov_ind,pi_i.rend(),is_larger);

        if(r_check != pi_i.end()){ // If there is a larger value in right direction...

            int r_ind =  std::find(pi_i.begin(), pi_i.end(), *r_check) - pi_i.begin();
            r_max = r_ind - mov_ind - 1; // ... the jump is reduced to be up to that value
            
        }
        else if (r_check == pi_i.end()){

            r_max = pi_i.size()-1-mov_ind; // right limit is the distance to the right edge

        }
        
        if(l_check != pi_i.rend()){ // If there is a larger value in left direction...

            int l_ind = std::find(pi_i.begin(), pi_i.end(), *l_check) - pi_i.begin();
            l_max = mov_ind - l_ind - 1; // ... the jump is reduced to be up to that value
            
        }

        else if (l_check == pi_i.rend()){ // If there are no larger values either end...
            
            l_max = mov_ind; // left limit is the distance to the left edge
        }

        std::cout << "R jump is: " << r_max << "\n";
        std::cout << "L jump is: " << l_max << "\n";

        std::vector<int> rcontainer;
        std::vector<int> lcontainer;
        bool rj_found = false;
        bool lj_found = false;

        for(int rjc = 1; rjc!=r_max+1; rjc++){ // search for a minimal right jump
            std::cout << "rjc is "  << rjc << "\n";
            rcontainer = r_jump(pi_i, mov_ind,rjc);

            auto rcontainer_valid = std::find(update_vec.begin(),update_vec.end(),rcontainer);

            std::cout << "\n";
            if(rcontainer_valid==update_vec.end() && PatternIsPresent(rcontainer,pattern)!=true){

                rj_found = true;

                std::cout << "PERM FOUND R!" << "\n";
                break;

           }
            else{

                ;

           }
        }

        for(int ljc = 1; ljc!=l_max+1; ljc++){ // search for a minimal left jump
            std::cout << "ljc is " << ljc << "\n";
            lcontainer = l_jump(pi_i, mov_ind,ljc);

            auto lcontainer_valid = std::find(update_vec.begin(),update_vec.end(),lcontainer);
            if(lcontainer_valid==update_vec.end() && PatternIsPresent(lcontainer,pattern)!=true){
               
               lj_found = true;
               std::cout << "PERM FOUND L!" << "\n";
               break;

            }
            else{
                ;
            }
        }

        if( rj_found && lj_found){ // if jump direction is ambiguous...

            return pi_i; // ...terminate Algorithm J
        }

        else if ( rj_found){ // if right jump found...

            return rcontainer; // ...return this jump
        }

        else if ( lj_found){ // if left jump foun ...

            return lcontainer; // ... return this jump
        }

        else{ // otherwise...
           
            continue; // ... continue to test next largest value
        
        }

    
    }
    
    return pi_i; // if no jumps possible for any value, terminate Algorithm J
}

std::vector<std::vector<int>> Algorithm_J(std::vector<int> init_vec, std::vector<int> pattern){

    /*  Performs Algorithm J, successive minimal jumps until jump direction ambiguous 
        or no jumps available.
        
        std::vector<int> 'init_vec': Initial permutation (pi_0) that is visited automatically
        std::vector<int> 'pattern': Pattern to be avoided

    */

    std::vector<std::vector<int>> visit_list; // List of visited permutations

	bool term_cond = false; // When true, Algorithm J will terminate and return visit_list
	visit_list.push_back(init_vec); // Visit the initial permutation pi_0
    
	while(term_cond == false){

        std::vector<int> last_perm = visit_list.back(); // access the latest permutation visited
		std::vector<int> new_perm = min_jump(last_perm, visit_list, pattern);
			
		if(last_perm == new_perm){ // If there is no change in the permutation...
			
			term_cond = true; // ... Terminate Algorithm J 
		
		}
		
		else {
		
			visit_list.push_back(new_perm); // Add the new permutation and continue minimal jumps
		}
	}
	
	return visit_list;
}

// +----------------+ //
// | MAIN BODY CODE | //
// +----------------+ //

int main(){

    std::vector<std::vector<int>> test1 = Algorithm_J({1,2,3,4},{2,3,1});

    printp_vec(test1);
    
}