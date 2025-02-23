## 1-2

**In a 64-bit system using 4KB pages, which bits are used to represent the page offset, and which are used to represent the page number?**

**How about for a 64-bit system using 2MB pages? Which bits are used for page number and which are for page offset?**

**In a 2GB buffer, how many 2MB hugepages are there?**

## 2-1

**Given a victim address 0x752C3000, what is the value of its Row id? The value of its Column id?**

**For the same address, assume an arbitrary XOR function for computing the Bank id, list all possible attacker addresses whose Row id is one more than 0x752C3000's Row id and all the other ids match, including the Bank id and Column id. Hint: there should be 16 such addresses total.**

## 2-3

**Report the statistics produced by your code when running part3, and describe how you can use the difference in these statistics to distinguish between the pairs.**

## 3-2

**Based on the XOR function you reverse-engineered, determine which of the 16 candidate addresses you derived in Discussion Question 2-1 maps to the same bank.**

## 4-2

**Include the bitflip observation statistics in the table below. Then answer the following questions:**

**Do your results match your expectations? Why might some attacker pairings result in more flips than others? Do you expect any of the pairs to never cause a flip?**

## 5-1

**Given the ECC type descriptions listed above, fill in the following table (assuming a data length of 4). For correction/detection, only answer "Yes" if it can always correct/detect (and "No" if there is ever a case where the scheme can fail to correct/detect). We've filled in the first line for you.**

## 5-3

**When a single bit flip is detected, describe how Hamming(22,16) can correct this error.**

## 5-5

**Can the Hamming(22,16) code we implemented always protect us from rowhammer attacks? If not, describe how a clever attacker could work around this scheme.**

