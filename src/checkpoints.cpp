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
        ( 199909,   uint256("0x740e26d507678dc6ed330a32c06b2bcde04b4ba0fadb7afcf3902562069ef54b") ) 
        ( 200009,   uint256("0x434126756e0d2c1725b1e28dc79ba0045e287abfbc36f5bb90228cc19e78171b") ) 
        ( 200909,   uint256("0x58104c2c111496807cb251b88a171feec37c150fc885f50778e06b1a847dd903") ) 
        ( 201009,   uint256("0x8d4bf9be4b40bca5eb939af3f6de3ab73989fa8bcc6eb738ff64874f7e9b4a4b") ) 
        ( 209009,   uint256("0xf509518051882886184c5294151506a370e1072cd21b8d5c7332ab4bd70cf5c8") ) 
        ( 220009,   uint256("0x74b9cd557fef4484b7d9dbb4afd6b3032676df91807b9e9d957ab319ec097523") ) 
        ( 236011,   uint256("0xf5de325d3daa42d6e238e36fe1dc694b0ef3e34b57ef31f2e9b282fba14649d9") ) 
        ( 250011,   uint256("0x0135bb56254f6391b19bf3f00b8550a26adb835037c6af158a4b080949afa596") ) 
        ( 260011,   uint256("0x454fe457551e40f73a4942293323504808dc5b30835ce218df00f59023b47878") ) 
        ( 270007,   uint256("0xf1eece6004c6be3c077cd9745ff3e464ea928fc9b70d7b6246550226bd9028b5") ) 
        ( 280009,   uint256("0x93a0417180cd3340214710764cb2d5fca0a2ddf706332ee5cd6a94e063ae5b58") ) 
        ( 290011,   uint256("0x4f9e294fdbd3953f360ffb913016f228523806b8b70f9d2c43a6308401858126") ) 
        ( 300000,   uint256("0xcb717d710334fa7487fe9ea5d4c84331fe3c112f785ed063f9de1c100d69393f") ) 
        ( 300101,   uint256("0xc5c17b0e59d8390eaaeecca8d6942e0441848fd4343783a1c4936ba321620579") ) 
        ( 301011,   uint256("0x32f751b86514477d02a3d4edcc28822ef7f397dcb20e8d54ab878799d5c4d137") ) 
        ( 309011,   uint256("0x141e1f80c1e3a2fcc8f73e561560ebe71b18a8eaf66a0d24edab397be9c78e33") ) 
        ( 310000,   uint256("0xac487692c1f2547643309b7ac195f2af126642fde3b78226d82a45f283d0ac65") ) 
        ( 310511,   uint256("0x5c553b70753586a4665be84dc04b925b8622e9f9620f4da896ccb311806962a8") ) 
        ( 311111,   uint256("0x418c14e4b57707d72b06e78d8476f4758305abf863673fa8e89faf25d6335923") ) 
        ( 326511,   uint256("0xb8f27e137dcda4bb4755d77cbaf63431b9281fcf80d661b0873953740bb74d48") ) 
        ( 338533,   uint256("0x5c478b2ed4e185f8dde07e056fd8d92982c503c8c2344a1cf1e6b3c6d6ed8afd") ) 
        ( 341544,   uint256("0xf13a59423545407acb671cd8c10f9e6d7e472fb35df54fb2447ef5aff9f969a0") ) 
        ( 359577,   uint256("0x3088af868891661bc574486e8993f903217e72b3ad9c0029c4c6ee4a5222d016") ) 
        ( 364599,   uint256("0xa3ccc9b521206e80a2b128bebc41e476f45718128f2fba398260a6fd3bb8e9ca") ) 
        ( 378522,   uint256("0x9a61e3a12c4d012114522ee43d1ad8245755870979a1c1e06a3ee9d9f4807c96") ) 
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
