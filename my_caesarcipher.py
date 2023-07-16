# -*- coding: utf-8 -*-

import string

filter1 = string.ascii_lowercase
filter2 = string.ascii_uppercase

def encrypt(data, key):
    rst = ""
    for k in range(len(data)):
        idx1 = filter1.find(data[k])
        idx2 = filter2.find(data[k])
        if idx1 != -1:
            rst += filter1[(idx1+key)%len(filter1)]
        elif idx2 != -1:
            rst += filter2[(idx2+key)%len(filter2)]
        else:
            rst += data[k]
    return rst

def decrypt(data, key):
    rst = ""
    for k in range(len(data)):
        idx1 = filter1.find(data[k])
        idx2 = filter2.find(data[k])
        if idx1 != -1:
            rst += filter1[(idx1-key)%len(filter1)]
        elif idx2 != -1:
            rst += filter2[(idx2-key)%len(filter2)]
        else:
            rst += data[k]
    return rst

def main():

    key = 17

    sample_enc_data = "zj r"
    sample_dec_data = "is a"

    assert encrypt(sample_dec_data, key) == sample_enc_data, encrypt(sample_dec_data, key) 
    assert decrypt(sample_enc_data, key) == sample_dec_data, decrypt(sample_enc_data, key) 

    real_enc_data = "Kyv ufdvjkzt trk (Wvczj jzcmvjkizj trklj fi Wvczj trklj) zj r jdrcc, kpgztrccp wliip, triezmfiflj drddrc. Kyvp riv fwkve trccvu yfljv trkj nyve bvgk rj zeuffi gvkj fi jzdgcp trkj nyve kyviv zj ef evvu kf uzjkzexlzjy kyvd wifd fkyvi wvczuj reu wvczevj. Trkj riv fwkve mrclvu sp yldrej wfi tfdgrezfejyzg reu wfi kyvzi rszczkp kf ylek mvidze. Kyviv riv dfiv kyre 70 trk sivvuj, kyflxy uzwwvivek rjjftzrkzfej giftcrzd uzwwvivek eldsvij rttfiuzex kf kyvzi jkreuriuj. Kyv wcrx zj kyv gyirjv nzky urjyvj: wcrx nyrk zj r ufdvjkzt trk"

    print(decrypt(real_enc_data, key))

if __name__ == '__main__':
    main()

