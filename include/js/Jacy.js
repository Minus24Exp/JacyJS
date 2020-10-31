const Jacy = (function () {
    class DevError extends Error {
        constructor(msg = '') {
            super(`[DevError]: ${msg}`)
        }
    }

    class jcObject {
        constructor(_class) {
            this.fields = {}
            this._class = _class
        }

        get(name) {
            if (!this.fields[name]) {
                throw new Error(`${name} is not defined`)
            }
            return this.fields[name]
        }

        set(name, value) {
            if (this.fields[name].is_val) {
                throw new Error(`Unable to reassign val ${name}`)
            }
            this.fields[name].val = value
        }

        define(name, field) {
            if (this.fields[name]) {
                throw new DevError(`Redefinition of field ${name}`)
            }
            this.fields[name] = field
        }

        call_method(name, ...args) {
            if (typeof this._class.methods[name] === 'function') {
                return this._class.methods[name](...args)
            }
            throw new DevError(`${name} is not a function`)
        }
    }

    class Class extends jcObject {
        constructor() {
            super();
            this.methods = {}
        }

        define_method(name, method) {
            if (this.methods[name]) {
                throw new DevError(`Redefinition of method ${name}`)
            }
            this.methods[name] = {is_val: true, method}
        }
    }

    class cObject extends Class {

    }

    const cInt = new class extends cObject {
        constructor() {
            super();

        }
    }

    class Int extends jcObject {
        constructor(val) {
            super()
            this.value = parseInt(val)
        }
    }

    class Float extends jcObject {
        constructor(val) {
            super()
            this.value = parseFloat(val)
        }
    }

    class String extends jcObject {
        constructor(val) {
            super()
            this.value = val
        }
    }

    return {
        Int,
        Float,
        String,
    }
})();
