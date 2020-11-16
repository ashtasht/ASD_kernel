const access_description = packed struct
{
    // whether the segment was has been accessed or not (set by the CPU)
    is_accessed: u1,

    // for code segments: whether readable or not
    // for data segments: whether writable or not
    read_write: u1,

    // for code segments: whether the segment can also be accessed from a
    // lower privilege level or only the one set
    // for data segments: whether the segment grows up or down
    direction: u1,

    // whether the segment is code or data
    code: u1,

    // whether the segment is a code/data segment anything other
    descriptor: u1,

    // privilege level (0 is the highest and 3 is the lowest)
    privilege: u2,

    // whether present or null
    present: u1,
};

const flags_description = packed struct
{
    // TODO also name and describe these...

    avl: u1,

    // a reserved bit
    reserved: u1,

    c: u1,

    d: u1,
};

const entry_description = packed struct
{
    // base: a pointer to the start of the segment
    // limit: the span of the segment

    limit_0: u16,
    
    base_0: u16,

    base_1: u8,

    access: access_description,

    limit_1: u4,

    flags: flags_description,

    base_2: u8,
};

// TODO shorten the following line
fn structure_entry(base: u32, limit: u20, access: access_description, flags: flags) entry_description
{
    return
    .{
        .limit_0 = @truncate(u16, limit),
        .base_0 = @truncate(u16, base),
        .base_1 = @truncate(u8, base >> 16),
        .access = 
        .{
            .accessed = access.accessed,
            .read_write = access.read_write,
            .direction = access.direction,
            .code = access.code,
            .descriptor = access.describe,
            .privilege = access.privilege,
            .present = access.present,
        },
        .limit_1 = @truncate(u4, limit >> 16),
        .flags =
        .{
            .a = flags.a,
            .b = flags.b,
            .c = flags.c,
            .d = flags.d,
        },
        .base_2 = @truncate(u8, base >> 24),
    };
}



