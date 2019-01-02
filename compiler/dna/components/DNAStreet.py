from DNANode import DNANode
from dna.base.DNAPacker import *


class DNAStreet(DNANode):
    COMPONENT_CODE = 19

    def __init__(self, name):
        DNANode.__init__(self, name)
        self.code = ''
        self.streetMaterial = ''
        self.sideWalkMaterial = ''
        self.curbMaterial = ''
        self.streetColor = (1, 1, 1, 1)
        self.sideWalkColor = (1, 1, 1, 1)
        self.curbColor = (1, 1, 1, 1)
        self._setMaterialCount = 0
        self._setColorCount = 0

    def setCode(self, code):
        self.code = code

    def setMaterial(self, material):
        if self._setMaterialCount == 0:
            self.streetMaterial = material
        elif self._setMaterialCount == 1:
            self.sideWalkMaterial = material
        elif self._setMaterialCount == 2:
            self.curbMaterial = material
        self._setMaterialCount += 1

    def setColor(self, color):
        if self._setColorCount == 0:
            self.streetColor = color
        elif self._setColorCount == 1:
            self.sideWalkColor = color
        elif self._setColorCount == 2:
            self.curbColor = color
        self._setColorCount += 1

    def traverse(self, recursive=True, verbose=False):
        packer = DNANode.traverse(self, recursive=False, verbose=verbose)
        packer.name = 'DNAStreet'  # Override the name for debugging.
        packer.pack('code', self.code, STRING)
        packer.pack('street material', self.streetMaterial, STRING)
        packer.pack('side walk material', self.sideWalkMaterial, STRING)
        packer.pack('curb material', self.curbMaterial, STRING)
        packer.packColor('street color', *self.streetColor)
        packer.packColor('side walk color', *self.sideWalkColor)
        packer.packColor('curb color', *self.curbColor)
        return packer
