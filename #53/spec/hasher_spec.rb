# frozen_string_literal: true

require 'hasher'

RSpec.describe Hasher do
  describe '#fnv1' do
    it "returns the provided string's hash using the 32-bit FNV-1 algorithm" do
      expect(Hasher.fnv1('hello', variant: 32)).to eq(3069866343)
    end
  end
end
