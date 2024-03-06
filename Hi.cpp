if (m[ex.opcode].type == "ari")
        {
            int &rd = reg[ex.rd1];
            rd = ex.ans;
            cout << "Write Back: " << reg[ex.rd1] << endl;
        }
        if (m[ex.opcode].type == "mem")
        {
            if (ex.opcode == "la")
            {
                int &rd = reg[ex.rd1];
                rd = ex.ans;
            }
        }