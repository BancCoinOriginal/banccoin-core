// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "txdb.h"
#include "main.h"
#include "uint256.h"


static const int nCheckpointSpan = 500;

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    // 
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        ( 0,   uint256("0x00000da9f638b705f00f8f6fc533aeed36e656996bf31ffc52d56dfdd6b25b5c") ) 
        ( 100,   uint256("0xa8bf6b2ef5e0d56f991681ad3af689ca230243e20ad3200011c23b498082d2df") ) 
        ( 510,   uint256("0xce18f2c1153e2c030618a05a1bee8e7dcead88f8b54b20521f69ddcdaed356d2") ) 
        ( 1010,   uint256("0x2f84b7589d9eb1eb0b167e57235f828b89a21186e8b6e110c17982bb993df5b3") ) 
        ( 5050,   uint256("0x72ea7a1164cefcf41c10bdb70323ba051e67b33de8be536879930e346bbc18bf") ) 
        ( 10010,   uint256("0xe3d5cb1ec5b3642e1484deca9719773b5474ad2503533bb4da5adbe461eb8aa0") ) 
        ( 51000,   uint256("0x5d4e4673ae13e9e0d333a00640d6962fc35a8fb56f166230aa01c1315da67955") ) 
        ( 81000,   uint256("0xac0d92378b7ac09e1814a016a9d1f64a846fd6b4c7fb9f158b00c32b950537f5") ) 
        ( 91000,   uint256("0x5beef44f6f5d0de6e9f5fda718c59b166c628ba16663ff5ed8cb34398a86119d") ) 
        ( 101000,   uint256("0xd7d4aa70b5144e133b0257660515a859e48e557306b3aa30465809ed5cc2e755") ) 
        ( 120001,   uint256("0xc926251e245663560fa8635f8d72ff17447035ccfb5eccd785544f6ef4862fe0") ) 
        ( 130003,   uint256("0x28cd692e1440204f73bbecb420281964851c084c6528f5501a88effac8043563") ) 
        ( 150003,   uint256("0x15005559eebf68a2da451734dda83329df6b2ee63c8b706a6f32516f1544f087") ) 
        ( 170003,   uint256("0x3df6434a6a99470e5567f95fce8ce7efe763a515ce06dc8c3fba9a23f32c9b4b") ) 
        ( 180008,   uint256("0x0847a784f81a2c351a9fdb100c48a5917b425eaf9fbeb116b95a17db9aa4bd13") ) 
        ( 190009,   uint256("0xbfd876d81f6d9dc1db9c5e5531e402362eae8923a4f6fa7aa213d31e0e5a15d6") ) 
    ;

    // TestNet has no checkpoints
    static MapCheckpoints mapCheckpointsTestnet;

    bool CheckHardened(int nHeight, const uint256& hash)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        if (checkpoints.empty())
            return 0;
        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }

    // Automatically select a suitable sync-checkpoint 
    const CBlockIndex* AutoSelectSyncCheckpoint()
    {
        const CBlockIndex *pindex = pindexBest;
        // Search backward for a block within max span and maturity window
        while (pindex->pprev && pindex->nHeight + nCheckpointSpan > pindexBest->nHeight)
            pindex = pindex->pprev;
        return pindex;
    }

    // Check against synchronized checkpoint
    bool CheckSync(int nHeight)
    {
        const CBlockIndex* pindexSync = AutoSelectSyncCheckpoint();

        if (nHeight <= pindexSync->nHeight)
            return false;
        return true;
    }
}
