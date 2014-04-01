program VOTE_PROG{
version VOTE_VERS{
        int ZEROIZE() = 1;
		int ADDVOTER(int) = 2;
		int VOTEFOR(string) = 3;
		string LISTCANDIDATES() = 4;
		int VOTECOUNT(string) = 5;
		} = 1;
		} = 0x21111111;