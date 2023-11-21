#include <bits/stdc++.h>
#include <ctime>

#define ll long long int
using namespace std;

struct Frame {
    ll seq_num;
    bool is_acknowledged;
};

void transmission(vector<Frame> & sender_buffer, ll & N, ll & tf, ll & tt) {
    ll base = 0;
    while (base <= tf) {
        // Send frames within the window
        for (ll i = base; i < min(base + N, tf); i++) {
            cout << "Sending Frame " << i << "..." << endl;
        }

        // Simulate acknowledgment reception for frames in the window
        for (ll i = base; i < min(base + N, tf); i++) {
            int f = rand() % 2;
            if (!f) {
                cout << "Acknowledgment for Frame " << i << "..." << endl;
                sender_buffer[i].is_acknowledged = true;
            } else {
                cout << "Timeout!! Frame Number : " << i << " Not Received" << endl;
                cout << "Retransmitting Frame " << i << "..." << endl;
                tt++;
                // Note: In SR, we retransmit individual frames upon timeout, not the entire window.
            }
        }

        // Move the window based on acknowledged frames
        while (base <= tf && sender_buffer[base].is_acknowledged) {
            base++;
        }
    }
}

int main() {
    ll tf, N, tt = 0;
    srand(time(NULL));
    cout << "Enter the Total number of frames : ";
    cin >> tf;
    cout << "Enter the Window Size : ";
    cin >> N;

    vector<Frame> sender_buffer(tf + 1);
    for (ll i = 1; i <= tf; i++) {
        sender_buffer[i].seq_num = i;
        sender_buffer[i].is_acknowledged = false;
    }

    transmission(sender_buffer, N, tf, tt);

    cout << "Total number of frames which were sent and resent are : " << tt << endl;
    return 0;
}