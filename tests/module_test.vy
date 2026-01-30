module vcore;
module vmem;
module CustomModule;

sub::CustomModule call(){
    log("hi");
}

log(vmem.usage(CustomModule.call));