# $Header$
def generate(env, **kw):
    if not kw.get('depsOnly', 0):
        env.Tool('addLibrary', library = ['eventFile'])
    env.Tool('facilitiesLib')

def exists(env):
    return 1;
