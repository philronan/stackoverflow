# See https://stackoverflow.com/q/63989851/1679849
# ---------------------------------------------------------------------------------
# Basically this code attempts to recover strings encoded by converting each
# character into its equivalent binary value (without leading zeros) and
# concatenating the results. This produces ambiguous results. For example:
#   encode_binary('password') = encode_binary('p0<|>>?%$') =
#   '11100001100001111001111100111110111110111111100101100100'
# To get the most likely value of the original string, this code generates
# all possible results, and then sorts them based on a simple heuristic that
# favours alphabet characters and spaces over digits and punctuation. The string
# with the highest score is returned as the result.
# ---------------------------------------------------------------------------------


def encode_binary(s):
    return ''.join(format(ord(i), 'b') for i in s)

def decode_binary(s):
    # -----------------------------------------------------------------------------
    # A list of all the possible input strings extracted by backtracking_search().
    # Each string is associated with a score
    candidates = []
    # -----------------------------------------------------------------------------
    # Calculate a score for the likelihood of a decoded string corresponding to the
    # original input. This could be made much more sophisticated if necessary. For
    # example, higher points could be awarted for the presence of dictionary words
    def score(t):
        r = 0
        for ch in t:
            if ch == ' ' or ch.isalpha():
                r += 1
            else:
                r -= 1
        return r
    # -----------------------------------------------------------------------------
    # Depth-first search fuction that parses an input string of binary digits into
    # 6- or 7-bit chunks corresponding to ASCII characters. The parameter s contains
    # the remaining input binary string, and t is a string containing the characters
    # extracted so far. All valid strings are added to the candidates[] array
    def dfs(s,t):
        if len(s) == 0:
            candidates.append((t, score(t)))
            return True
        if len(s) < 6 or s[0]=='0':
            return False
        c1 = chr(int(s[:6],2))
        ok = False
        if dfs(s[6:], t+c1):
            ok = True
        if len(s) >= 7:
            c2 = chr(int(s[:7],2))
            if dfs(s[7:], t+c2):
                ok = True
        return ok
    # -----------------------------------------------------------------------------
    # Extract all candidate texts and extract the one with the highest score
    # dfs(s, '')
    # candidates.sort(key=lambda c: -c[1])
    # Uncomment these lines if you want to see the top candidates
    print(len(candidates))
    print(candidates[:6])
    return candidates[0][0]

decode_binary(encode_binary("Have you got anything without spam?"))
