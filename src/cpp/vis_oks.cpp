// int main() {
//     cin.tie(0);
//     ios::sync_with_stdio(false);

//     readInput();

//     for (int y = 0; y < N; y++) {
//         for (int x = 0; x < N; x++) {
//             {
//                 int x1 = x;
//                 int y1 = y;
//                 int x2 = x + 1;
//                 int y2 = y + 1;
//                 int x3 = x;
//                 int y3 = y + 2;
//                 int x4 = x - 1;
//                 int y4 = y + 1;
//                 bool ok = true;
//                 if (!(0 <= x1 && x1 < N)) ok = false;
//                 if (!(0 <= x2 && x2 < N)) ok = false;
//                 if (!(0 <= x3 && x3 < N)) ok = false;
//                 if (!(0 <= x4 && x4 < N)) ok = false;
//                 if (!(0 <= y1 && y1 < N)) ok = false;
//                 if (!(0 <= y2 && y2 < N)) ok = false;
//                 if (!(0 <= y3 && y3 < N)) ok = false;
//                 if (!(0 <= y4 && y4 < N)) ok = false;
//                 if (ok) {
//                     Rect r1(y1, x1, y2, x2, y3, x3, y4, x4, -1);
//                     if (r1.is_ok(3)) {
//                         cout << r1 << endl;
//                     }
//                 }
//             }
//             {
//                 int x1 = x;
//                 int y1 = y;
//                 int x2 = x + 1;
//                 int y2 = y;
//                 int x3 = x + 1;
//                 int y3 = y + 1;
//                 int x4 = x;
//                 int y4 = y + 1;
//                 bool ok = true;
//                 if (!(0 <= x1 && x1 < N)) ok = false;
//                 if (!(0 <= x2 && x2 < N)) ok = false;
//                 if (!(0 <= x3 && x3 < N)) ok = false;
//                 if (!(0 <= x4 && x4 < N)) ok = false;
//                 if (!(0 <= y1 && y1 < N)) ok = false;
//                 if (!(0 <= y2 && y2 < N)) ok = false;
//                 if (!(0 <= y3 && y3 < N)) ok = false;
//                 if (!(0 <= y4 && y4 < N)) ok = false;
//                 if (ok) {
//                     Rect r2(y1, x1, y2, x2, y3, x3, y4, x4, -1);
//                     if (r2.is_ok(3)) {
//                         cout << r2 << endl;
//                     }
//                 }
//             }
//         }
//     }

//     return 0;

//     timer.start();
//     solve();
//     timer.stop();

// #ifdef hari64
//     assert(timer.ms() < TL);
// #endif

//     return 0;
// }
