#define BIT(x) (1UL << (x))

#define SET_BIT(var, pos) (var |= 1UL << (pos))
#define CLR_BIT(var, pos) (var &= ~(1UL << (pos)))

#define SET_BITS(var, pos_low, pos_high) (var |= BITMASK(pos_high - pos_low + 1) << (pos))
#define CLR_BITS(var, pos_low, pos_high) (var &= ~(BITMASK(pos_high - pos_low + 1) << (pos)))

#define BITMASK(size) (1UL << (size) - 1)

