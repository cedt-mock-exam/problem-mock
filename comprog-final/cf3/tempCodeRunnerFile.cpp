else if (cur == 5) {
            //     vector<ll> temp = favors;
            //     sort(temp.begin(), temp.end());
            //     ll sus = rnd.next(1, 130); // 1.0% - 13.0% of present size
            //     sus = (favors.size() * sus + 1000) / 1000;
            //     sus--; // based 0 index
            //     assert(0 <= sus && sus < favors.size());
            //     ll val = rnd.next((sus == 0 ? 0 : temp[sus - 1]), temp[sus]);
            //     auto it = favors.begin();
            //     while (it != favors.end()) {
            //         if (*it < val) {
            //             it = favors.erase(it);
            //         }
            //         else {
            //             it++;
            //         }
            //     }
            //     cout << val << endl;
            //     temp.clear();
            // }
            // else if (cur == 6) {
            //     ll val = rnd.next(1, 130); // 1.0% - 13.0% of present size
            //     val = (favors.size() * val + 1000) / 1000;
            //     ll sum = 0;
            //     for (int i = 0; i < val; i++) {
            //         sum += favors.back();
            //         favors.pop_back();
            //     }
            //     favors.insert(favors.begin(), sum);
            //     cout << val << endl;
            // }