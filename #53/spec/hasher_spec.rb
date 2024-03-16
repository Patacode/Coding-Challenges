# frozen_string_literal: true

require 'hasher'

RSpec.describe Hasher do
  describe '#fnv1' do
    it "returns the provided string's hash using the 32-bit FNV-1 algorithm" do
      expect(Hasher.fnv1('hello', variant: 32)).to eq(3_069_866_343)
    end

    it "returns the provided string's hash using the 64-bit FNV-1 algorithm" do
      expect(Hasher.fnv1('hello', variant: 64)).to eq(8_883_723_591_023_973_575)
    end
  end
end
