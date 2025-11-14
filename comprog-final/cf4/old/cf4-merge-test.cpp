#include "testlib.h"
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

struct MergeNode {
  int position;
  int order;
};

// Function to simulate merge operation with group size limit
vector<vector<MergeNode>> test_merge(const vector<vector<MergeNode>> &groups,
                                     int k, int maxGroupSize = -1) {
  vector<vector<MergeNode>> result;
  vector<bool> used(groups.size(), false);

  for (int i = 0; i < groups.size(); i++) {
    if (used[i]) continue;

    vector<MergeNode> newGroup = groups[i];
    int leftmostPos = groups[i][0].position; // base position
    used[i] = true;

    // Find all groups that can merge with this one
    for (int j = i + 1; j < groups.size(); j++) {
      if (used[j]) continue;

      int otherPos = groups[j][0].position; // base position of other group
      if (abs(otherPos - leftmostPos) <= k) {
        // Check if merging would exceed group size limit
        if (maxGroupSize != -1 && (int)newGroup.size() + (int)groups[j].size() > maxGroupSize) {
          continue; // Skip this merge to respect group size limit
        }

        // Merge groups - stack by order of bottommost elements
        if (groups[j][0].order < newGroup[0].order) {
          // Other group goes to bottom
          vector<MergeNode> temp = groups[j];
          temp.insert(temp.end(), newGroup.begin(), newGroup.end());
          newGroup = temp;
          leftmostPos = groups[j][0].position;
        } else {
          // Current group stays at bottom
          newGroup.insert(newGroup.end(), groups[j].begin(), groups[j].end());
        }
        used[j] = true;
      }
    }

    // Update positions to base position
    for (auto &elem : newGroup) {
      elem.position = leftmostPos;
    }

    result.push_back(newGroup);
  }

  return result;
}

int main(int argc, char **argv) {
  registerGen(argc, argv, 1);

  int depth, amount, b;
  cout << "Enter depth, amount, and max group size (b, -1 for no limit): ";
  cin >> depth >> amount >> b;

  // Special case: if b = 1, we can't have any merging at all
  if (b == 1) {
    cout << "\nWith b = 1, no merging is possible. All elements remain separate." << endl;
    
    // Generate initial array of pairs
    vector<MergeNode> elements(amount);
    set<int> usedOrders;

    // Generate unique orders from 1 to amount
    for (int i = 0; i < amount; i++) {
      int order;
      do {
        order = rnd.next(1, amount);
      } while (usedOrders.count(order));
      usedOrders.insert(order);
      elements[i].order = order;
    }

    // Generate positions between -100 and 100
    vector<int> positions;
    set<int> usedPositions;
    
    for (int i = 0; i < amount; i++) {
      int pos;
      do {
        pos = rnd.next(-100, 100);
      } while (usedPositions.count(pos));
      usedPositions.insert(pos);
      positions.push_back(pos);
    }

    // Assign positions to elements
    for (int i = 0; i < amount; i++) {
      elements[i].position = positions[i];
    }

    // Sort by position as required
    sort(elements.begin(), elements.end(),
         [](const MergeNode &a, const MergeNode &b) {
           return a.position < b.position;
         });

    // Output results
    cout << "\nGenerated array of pairs:" << endl;
    cout << "[";
    for (int i = 0; i < elements.size(); i++) {
      cout << "{{" << elements[i].position << ", " << elements[i].order << "}}";
      if (i < elements.size() - 1) cout << ", ";
    }
    cout << "]" << endl;

    // For b = 1, any k-values will result in no merging
    cout << "\nK-values array (any values work since no merging occurs):" << endl;
    cout << "[";
    for (int i = 0; i < depth; i++) {
      cout << rnd.next(1, 50); // Random k-values that don't matter
      if (i < depth - 1) cout << ", ";
    }
    cout << "]" << endl;

    return 0;
  }

  // Generate initial array of pairs
  vector<MergeNode> elements(amount);
  set<int> usedOrders;

  // Generate unique orders from 1 to amount
  for (int i = 0; i < amount; i++) {
    int order;
    do {
      order = rnd.next(1, amount);
    } while (usedOrders.count(order));
    usedOrders.insert(order);
    elements[i].order = order;
  }

  // Generate positions strategically to allow for controlled merging with group size limits
  vector<int> positions;
  
  // Create clusters that can merge within the group size limit
  int clusters = max(1, amount / b); // Number of potential clusters
  int basePos = -80;
  int clusterSpacing = 160 / clusters; // Spread clusters across [-80, 80]
  
  for (int cluster = 0; cluster < clusters; cluster++) {
    int clusterCenter = basePos + cluster * clusterSpacing;
    int elementsInCluster = min(b, amount - cluster * b);
    
    for (int i = 0; i < elementsInCluster && positions.size() < amount; i++) {
      positions.push_back(clusterCenter + rnd.next(-5, 5)); // Small variation within cluster
    }
  }
  
  // Fill remaining positions if any
  while (positions.size() < amount) {
    positions.push_back(rnd.next(-100, 100));
  }

  // Ensure uniqueness
  set<int> usedPositions(positions.begin(), positions.end());
  while (usedPositions.size() < amount) {
    int newPos = rnd.next(-100, 100);
    if (usedPositions.find(newPos) == usedPositions.end()) {
      usedPositions.insert(newPos);
      positions.push_back(newPos);
    }
  }
  positions.resize(amount);

  // Assign positions to elements
  for (int i = 0; i < amount; i++) {
    elements[i].position = positions[i];
  }

  // Sort by position as required
  sort(elements.begin(), elements.end(),
       [](const MergeNode &a, const MergeNode &b) {
         return a.position < b.position;
       });

  // Generate K values that will create the desired depth
  vector<int> kValues;

  // Start with individual elements as groups
  vector<vector<MergeNode>> currentGroups;
  for (const auto &elem : elements) {
    currentGroups.push_back({elem});
  }

  // For each merge operation, calculate appropriate k value
  for (int d = 0; d < depth; d++) {
    if (currentGroups.size() <= 1) break;

    // Calculate distances between adjacent groups
    vector<int> distances;
    for (int i = 0; i < currentGroups.size() - 1; i++) {
      int dist = abs(currentGroups[i + 1][0].position - currentGroups[i][0].position);
      distances.push_back(dist);
    }

    if (distances.empty()) break;

    sort(distances.begin(), distances.end());

    // Find a k that will actually merge some groups within the size limit
    int k = -1;
    for (int testK : distances) {
      vector<vector<MergeNode>> testResult = test_merge(currentGroups, testK, b);
      if (testResult.size() < currentGroups.size()) {
        k = testK;
        break;
      }
    }
    
    // If no distance works, try slightly larger values
    if (k == -1) {
      for (int testK = distances[0] + 1; testK <= distances.back() + 10; testK++) {
        vector<vector<MergeNode>> testResult = test_merge(currentGroups, testK, b);
        if (testResult.size() < currentGroups.size()) {
          k = testK;
          break;
        }
      }
    }

    if (k == -1) break; // Can't merge any more

    kValues.push_back(k);
    currentGroups = test_merge(currentGroups, k, b);

    // If we've merged everything possible, we're done
    if (currentGroups.size() <= 1) break;
  }

  // Output results
  cout << "\nGenerated array of pairs:" << endl;
  cout << "[";
  for (int i = 0; i < elements.size(); i++) {
    cout << "{{" << elements[i].position << ", " << elements[i].order << "}}";
    if (i < elements.size() - 1) cout << ", ";
  }
  cout << "]" << endl;

  cout << "\nK-values array:" << endl;
  cout << "[";
  for (int i = 0; i < kValues.size(); i++) {
    cout << kValues[i];
    if (i < kValues.size() - 1) cout << ", ";
  }
  cout << "]" << endl;

  // Debug: Show final group structure
  cout << "\nFinal group structure:" << endl;
  for (int i = 0; i < currentGroups.size(); i++) {
    cout << "Group " << i + 1 << " (size " << currentGroups[i].size() << "): ";
    for (const auto& node : currentGroups[i]) {
      cout << "(" << node.position << "," << node.order << ") ";
    }
    cout << endl;
  }

  return 0;
}